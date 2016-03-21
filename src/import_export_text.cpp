//in import_export_text.cpp

#include "import_export_text.h"
#include <fstream>
#include <sstream>

void textImport(int max_row, std::string file_path, std::vector<long double>* data){
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
    data->at(r) = strtold(id.c_str(), NULL);
    inFile.getline (wholerow,1000);
  }
  inFile.close();
}

void textExport(int max_row, std::string file_path, std::vector<long double>* data){
  //Opening the file
  std::ofstream outFile;
  outFile.open(file_path.c_str());
  
  //Looping through the data, converting it to strings and writing onto the datafile
  std::string line_input;
  for(int i = 0; i<max_row; i++){
    line_input = std::to_string(data->at(i))+"\n";
    outFile << line_input;
  }
  outFile.close();
}
