// in text_import_text.cpp

#include "text_import_text.h"
#include <fstream>

void textImportText(int max_row, std::string file_path, std::vector<std::string>* data){
  //Function assumes that it is being passed a std::vector pointer that has been initialized in the made function
  std::string file = file_path;
  int n = max_row;
  // Initializing the files
  std::ifstream inFile;
  inFile.open(file.c_str());
  //List of Other Vars to Declare
  std::string id;
  char v1[1000], wholerow[1000];
  
  for(int r=0; r<n; r++){
    inFile >> v1;
    id = v1;
    //Stuffing the std::vector
    data->at(r) = id;
    inFile.getline (wholerow,1000);
  }
  inFile.close();
  
}