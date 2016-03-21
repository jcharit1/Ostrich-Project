// import_para.cpp

#include "import_para.h"
#include "splitLinetoStringVec.h"
#include <fstream>

void importPara(std::string file_path, std::vector< std::vector<std::string>*>* inputVec) {
  std::ifstream inFile;
  inFile.open(file_path.c_str());
  char wholerow[1000];
  std::string wholerow_str;
  
  for(int i=0; i<7; i++){
    inFile.getline (wholerow,1000);
    wholerow_str = wholerow;
    splitLinetoStringVec(wholerow_str, inputVec->at(i), ' ');
  }
  inFile.close();
}