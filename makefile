##Ostrich Program makefile
#Compiling time is not an issue, I didn't include intermediate *.o file creation

CC=g++
CFLAGS=-Wall -g -Ofast -Wno-unused-variable -Wno-unused-but-set-variable
LIB=-std=c++0x -pthread
INC= -I include
SRCDIR= src

#Shared sourcesEXE_RS
FILES= Ostrich.cpp combinatorial.cpp distribution.cpp file_functions.cpp investor_data.cpp investorResultsFileName.cpp makeActWealthPart.cpp makeComparable.cpp mix.cpp NDiscrete.cpp part_functions.cpp restore_point.cpp splitLinetoVec.cpp vec_functions.cpp vec_stat.cpp
SOURCES = $(FILES:%.cpp=$(SRCDIR)/%.cpp)

#Standard Utility Function Definition
FILES_STD_UTILITY=utility.cpp
SOURCES_STD_UTILITY = $(FILES_STD_UTILITY:%.cpp=$(SRCDIR)/%.cpp)

#John's 08-06-2016 Alternative Utility Definition
FILES_ALT_UTILITY_EXP1=utility_exp_1.cpp
SOURCES_ALT_UTILITY_EXP1 = $(FILES_ALT_UTILITY_EXP1:%.cpp=$(SRCDIR)/%.cpp)

#Riemann Sum Version of Main Program
FILES_RS=J_RS.cpp investorThread.cpp 
SOURCES_RS=$(FILES_RS:%.cpp=$(SRCDIR)/%.cpp)
EXE_RS=ProgramOneFinalRS

#Riemann Sum Version of Main Program, John's 08-06-2016 Alternative Utility Definition
FILES_RS_Alt_Ult=$(FILES_RS) 
SOURCES_RS_Alt_Ult=$(SOURCES_RS)
EXE_RS_Alt_Ult=ProgramOneFinalAltUtility

#Riemann Sum Detailed Output Version of Main Program
FILES_RS_D=J_RS.cpp investorThreadDetailed.cpp import_export_text.cpp 
SOURCES_RS_D=$(FILES_RS:%.cpp=$(SRCDIR)/%.cpp)
EXE_RS_D=ProgramOneFinalRS_Detailed

#Riemann Sum Detailed Output Version of Main Program, John's 08-06-2016 Alternative Utility Definition
FILES_RS_Alt_Ult_D=$(FILES_RS_D) 
SOURCES_RS_Alt_Ult_D=$(SOURCES_RS_D)
EXE_RS_Alt_Ult_D=ProgramOneFinalAltUtility_Detailed

#Beta=0 Closed Form Version of Main Program
FILES_B0=J_B0.cpp investorThread.cpp 
SOURCES_B0=$(FILES_B0:%.cpp=$(SRCDIR)/%.cpp)
EXE_B0=ProgramOneFinalRSB0

#Beta=0 Closed Form Detained Output Version of Main Program
FILES_B0_D=J_B0.cpp investorThreadDetailed.cpp import_export_text.cpp
SOURCES_B0_D=$(FILES_B0:%.cpp=$(SRCDIR)/%.cpp)
EXE_B0_D=ProgramOneFinalRSB0_Detailed

#Parent Ostrich Program Definition for Managing Calls to Main Program
FILES_Par= ParentOstrich.cpp investorListFileName.cpp import_export_text.cpp import_para.cpp programLocation.cpp investorDataFileName.cpp text_import_text.cpp file_functions.cpp investorResultsFileName.cpp SGE.cpp splitLinetoStringVec.cpp
SOURCES_Par=$(FILES_Par:%.cpp=$(SRCDIR)/%.cpp)
EXE_Par=ParentOstrich

all: $(EXE_RS) $(EXE_B0) $(EXE_Par) $(EXE_RS_D) $(EXE_B0_D) $(EXE_RS_Alt_Ult) $(EXE_RS_Alt_Ult_D)

$(EXE_RS): $(SOURCES_RS) $(SOURCES_STD_UTILITY) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_STD_UTILITY) $(SOURCES_RS) $(SOURCES) -o bin/$(EXE_RS)

$(EXE_RS_Alt_Ult): $(SOURCES_RS_Alt_Ult) $(SOURCES_ALT_UTILITY_EXP1) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_ALT_UTILITY_EXP1) $(SOURCES_RS_Alt_Ult) $(SOURCES) -o bin/$(EXE_RS_Alt_Ult)

$(EXE_B0): $(SOURCES_B0) $(SOURCES_STD_UTILITY) $(SOURCES) 
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_B0) $(SOURCES_STD_UTILITY) $(SOURCES) -o bin/$(EXE_B0)

$(EXE_Par): $(SOURCES_Par)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_Par) -o bin/$(EXE_Par)

$(EXE_RS_D): $(SOURCES_RS_D) $(SOURCES_STD_UTILITY) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_RS_D) $(SOURCES_STD_UTILITY) $(SOURCES) -o bin/$(EXE_RS_D)

$(EXE_RS_Alt_Ult_D): $(SOURCES_RS_Alt_Ult_D) $(SOURCES_ALT_UTILITY_EXP1) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_ALT_UTILITY_EXP1) $(SOURCES_RS_Alt_Ult_D) $(SOURCES) -o bin/$(EXE_RS_Alt_Ult_D)

$(EXE_B0_D): $(SOURCES_B0_D) $(SOURCES_STD_UTILITY) $(SOURCES) 
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_B0_D) $(SOURCES_STD_UTILITY) $(SOURCES) -o bin/$(EXE_B0_D)

clean:
	rm bin/$(EXE_RS) bin/$(EXE_B0) bin/$(EXE_Par) bin/$(EXE_RS_D) bin/$(EXE_B0_D) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_RS:
	rm bin/$(EXE_RS) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_RS_Alt_UTL:
	rm bin/$(EXE_RS_Alt_Ult) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_B0:
	rm bin/$(EXE_B0) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_Par:
	rm bin/$(EXE_Par) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_RS_D:
	rm bin/$(EXE_RS_D) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_RS_Alt_UTL_D:
	rm bin/$(EXE_RS_Alt_Ult_D) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_B0_D:
	rm bin/$(EXE_B0_D) *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

clean_back_up:
	rm *~ test/*~ doc/*~ src/*Rhistory src/*~ include/*~

test_1:
	./bin/ProgramOneFinalRSB0 ./test/test_investor_data/88808sample74.txt 88808 504 Test 0.0 0.0 3.0 1.0 0.5 10.0 10 1 RS 1000 0.001 0.001 Test F T F

test_2:
	./bin/ProgramOneFinalRS ./test/test_investor_data/88808sample74.txt 88808 504 Test 0.0 0.8 3.0 1.0 0.5 10.0 10 1 RS 1000 0.001 0.001 Test F T F

test_3:
	./bin/ProgramOneFinalAltUtility ./test/test_investor_data/88808sample74.txt 88808 504 Test 0.0 0.8 3.0 1.0 0.5 10.0 10 1 RS 1000 0.001 0.001 Test F T F
