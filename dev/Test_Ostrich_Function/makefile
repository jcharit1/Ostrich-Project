##Ostrich Program makefile
#Compiling time is not an issue, I didn't include intermediate *.o file creation

CC=g++
CFLAGS=-Wall -g -Ofast -Wno-unused-variable -Wno-unused-but-set-variable
LIB=-std=c++0x -pthread
INC= -I ../../include
SRCDIR= ../../src

#Shared sourcesEXE_RS
FILES= test_ostrich_function.cpp OstrichFunction.cpp combinatorial.cpp distribution.cpp file_functions.cpp investor_data_function.cpp makeActWealthPart.cpp makeComparable.cpp mix.cpp NDiscrete.cpp part_functions.cpp splitLinetoVec.cpp  vec_functions.cpp vec_stat.cpp
SOURCES = $(FILES:%.cpp=$(SRCDIR)/%.cpp)

#Standard Utility
FILES_STD_UTILITY=utility.cpp
SOURCES_STD_UTILITY = $(FILES_STD_UTILITY:%.cpp=$(SRCDIR)/%.cpp)

#Johns 08-06-2016 Alt utility
FILES_ALT_UTILITY_EXP1=utility_exp_1.cpp
SOURCES_ALT_UTILITY_EXP1 = $(FILES_ALT_UTILITY_EXP1:%.cpp=$(SRCDIR)/%.cpp)

#Riemann Sum version
FILES_RS=J_RS_Function.cpp investorThreadFunction.cpp 
SOURCES_RS=$(FILES_RS:%.cpp=$(SRCDIR)/%.cpp)
EXE_RS=OstrichFunction

#Beta=0 closed form version
FILES_B0=J_B0_Function.cpp investorThreadFunction.cpp 
SOURCES_B0=$(FILES_B0:%.cpp=$(SRCDIR)/%.cpp)
EXE_B0=OstrichFunctionB0

all: $(EXE_RS) $(EXE_B0)

$(EXE_RS): $(SOURCES_RS) $(SOURCES_STD_UTILITY) $(SOURCES)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_STD_UTILITY) $(SOURCES_RS) $(SOURCES) -o ../../bin/$(EXE_RS)

$(EXE_B0): $(SOURCES_B0) $(SOURCES_STD_UTILITY) $(SOURCES) 
	$(CC) $(CFLAGS) $(LIB) $(INC) $(SOURCES_B0) $(SOURCES_STD_UTILITY) $(SOURCES) -o ../../bin/$(EXE_B0)

clean:
	rm ../../bin/$(EXE_RS) ../../bin/$(EXE_B0) *~ ../../test/*~ ../../doc/*~ ../../src/*Rhistory ../../src/*~ ../../include/*~

clean_RS:
	rm ../../bin/$(EXE_RS) *~ ../../test/*~ ../../doc/*~ ../../src/*Rhistory ../../src/*~ ../../include/*~

clean_B0:
	rm ../../bin/$(EXE_B0) *~ ../../test/*~ ../../doc/*~ ../../src/*Rhistory ../../src/*~ ../../include/*~

clean_back_up:
	rm *~ ../../test/*~ ../../doc/*~ ../../src/*Rhistory ../../src/*~ ../../include/*~

test_1:
	../../bin/OstrichFunction

test_2:
	../../bin/OstrichFunctionB0

