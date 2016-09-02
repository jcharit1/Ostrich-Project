//in investor_data.cpp

#include "investor_data_function.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

void importInvestorData(int max_row, std::string file_path, std::vector<std::vector<long double>* >* data){
  //Function assumes that it is being passed a std::vector pointer that has been initialized in the made function
  std::string file = file_path;
  int n = max_row;
  
  // Initializing the files
  std::ifstream inFile;
  inFile.open(file.c_str());
  
  //List of Other Vars to Declare
  std::string id, logged_y1, rjp, rmkt;
  char v1[1000], v2[1000], v3[1000], v4[1000], wholerow[1000];
  
  for(int row=0; row<n; row++){
    inFile >> v1 >> v2 >> v3 >> v4;
    id = v1;
    logged_y1 = v2;
    rjp = v3;
    rmkt = v4;
    
    //Stuffing the std::vector
    (data->at(0))->at(row) = strtold(id.c_str(), NULL); // col 0
    (data->at(1))->at(row) = strtold(logged_y1.c_str(), NULL); // col 1
    (data->at(2))->at(row) = strtold(rjp.c_str(), NULL); // col 2
    (data->at(3))->at(row) = strtold(rmkt.c_str(), NULL); // col 3
    
    inFile.getline (wholerow,1000);
  }
  inFile.close();
}

void getInvestorData(std::vector<std::vector<long double>* >* all_data, std::vector<long double>* investor_ids, std::vector<std::vector<long double> >* investor_data, std::vector<std::vector<std::vector<long double> > >* investor_all) {
  //Note to self, passing investor_data* is wasteful, pass int investor_data.size()
  int j = 0;
  for(int i = 0; i< (signed int) ((all_data->at(0))->size()); i++) {
    if ((investor_ids->at(j))==((all_data->at(0))->at(i))){
      for(int k=0; k< (signed int) investor_data->size(); k++){
        ((investor_all->at(j)).at(k)).push_back((all_data->at(k))->at(i));
      }
    }
    else {
      //move to the next investor matrix
      j = j+1;
      for(int k=0; k< (signed int) investor_data->size(); k++){
        ((investor_all->at(j)).at(k)).push_back((all_data->at(k))->at(i));
      }
    }
  }
}