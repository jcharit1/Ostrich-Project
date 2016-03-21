CC=g++
CFLAGS=-Wall -g -Ofast -Wno-unused-variable -Wno-unused-but-set-variable
LIB=-std=c++0x -pthread
INC= -I include
SRCDIR= src

#Shared sources
FILES= Ostrich.cpp investorThread.cpp combinatorial.cpp distribution.cpp file_functions.cpp investor_data.cpp investorResultsFileName.cpp makeActWealthPart.cpp makeComparable.cpp mix.cpp NDiscrete.cpp part_functions.cpp restore_point.cpp splitLinetoVec.cpp  vec_functions.cpp vec_stat.cpp
SOURCES = $(FILES:%.cpp=$(SRCDIR)/%.cpp)

#Riemann Sum version
FILES_RS=J_RS.cpp utility.cpp 
SOURCES_RS=$(FILES_RS:%.cpp=$(SRCDIR)/%.cpp)
EXE_RS=ProgramOneFinalRS

#Beta=0 closed form version
FILES_B0=J_B0.cpp 
SOURCES_B0=$(FILES_B0:%.cpp=$(SRCDIR)/%.cpp)
EXE_BO=ProgramOneFinalRSB0

#Parent Ostrich
FILES_Par= ParentOstrich.cpp investorListFileName.cpp import_export_text.cpp import_para.cpp programLocation.cpp investorDataFileName.cpp text_import_text.cpp file_functions.cpp investorResultsFileName.cpp SGE.cpp splitLinetoStringVec.cpp
SOURCES_Par=$(FILES_Par:%.cpp=$(SRCDIR)/%.cpp)
EXE_Par=ParentOstrich

all: $(EXE_RS) $(EXE_BO) $(EXE_Par)

$(EXE_RS): $(SOURCES_RS) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_RS) $(SOURCES) -o bin/$(EXE_RS)

$(EXE_BO): $(SOURCES_B0) $(SOURCES) 
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_B0) $(SOURCES) -o bin/$(EXE_BO)

$(EXE_Par): $(SOURCES_Par)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_Par) -o bin/$(EXE_Par)

clean:
	rm $(EXE_RS) $(EXE_BO) $(EXE_Par) *~

clean_RS:
	rm $(EXE_RS) *~

clean_B0:
	rm $(EXE_BO) *~

clean_Par:
	rm $(EXE_Par) *~


