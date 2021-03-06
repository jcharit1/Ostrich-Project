//in restore_point.cpp

#include "restore_point.h"
#include "file_functions.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

bool getRestorePoint(std::string restoreFile, std::vector<std::vector<long double> >* new_LDL, std::vector<std::vector<long double> >* prev_LDL, long double LDL_num_rows, long double LDL_num_cols, long double* period, std::string checkPoint) {
  if (checkPoint == "F"){
    return false;
  }

  //checking iF file can be opened and the number of lines in the file is correct
  long double rightNumLines = 2*LDL_num_cols*LDL_num_rows + 1; //2*(# of cols in LDL vecs)*(# of rows in LDL vecs)*2 + 1, plus 1 for the period var and times 2 for the prev_LDL and new_LDL vectors
  bool proceed = false;
  if (fileExistStat(restoreFile)){
    //it exist but was state saving processing interrupted before all the necessary data was saved?
    proceed = (countFileLines(restoreFile)==rightNumLines);
  }

  if (proceed){
    //filling the vectors with "air" before stuffing them
    if(new_LDL->size() == 0){
      new_LDL->resize(LDL_num_cols);
      for(int i = 0; i < LDL_num_cols; i++){
        (new_LDL->at(i)).resize(LDL_num_rows);
      }
    }
    if(prev_LDL->size() == 0){
      prev_LDL->resize(LDL_num_cols);
      for(int i = 0; i < LDL_num_cols; i++){
        (prev_LDL->at(i)).resize(LDL_num_rows);
      }
    }

    // Initializing the file
    std::ifstream inFile;
    inFile.open(restoreFile.c_str());

    //Helper variables for pulling data out of the file
    std::string data;
    char v1[1000], wholerow[1000];

    //Filing in the LDL vectors
    for(int col = 0; col < (signed int) new_LDL->size(); col++){
      for(int row = 0; row < (signed int) (new_LDL->at(col)).size(); row++){
        inFile >> v1;
        data = v1;
        (new_LDL->at(col))[row] = strtold(data.c_str(), NULL);
        inFile.getline (wholerow,1000);
      }
    }
    for(int col = 0; col < (signed int) prev_LDL->size(); col++){
      for(int row = 0; row < (signed int) (prev_LDL->at(col)).size(); row++){
        inFile >> v1;
        data = v1;
        (prev_LDL->at(col))[row] = strtold(data.c_str(), NULL);
        inFile.getline (wholerow,1000);
      }
    }
    //Filing in the period variable
    inFile >> v1;
    data = v1;
    *period = strtold(data.c_str(), NULL);
    inFile.getline (wholerow,1000);
    inFile.close(); //close the file
    //I imported it with all the expected rows
    return true;
  }
  else {
    //can't open it, start over
    return false;
  }
}

void createRestorePoint(std::string restoreFile, std::vector<std::vector<long double> >* new_LDL, std::vector<std::vector<long double> >* prev_LDL, long double period, std::string checkPoint){
  if (checkPoint == "T") {
    //Removing the current file if it exist
    if (fileExistStat(restoreFile)) {
      std::string comd = "rm "+restoreFile;
      int sysMsg = system(comd.c_str());
    }

    //Opening the file
    std::ofstream outFile;
    outFile.open(restoreFile.c_str());

    //Looping through the data, converting it to strings and writing onto the datafile
    std::string line_input;
    //Adding in the new_LDL std::vector
    for(int col = 0; col < (signed int) new_LDL->size(); col++){
      for(int row = 0; row < (signed int) (new_LDL->at(col)).size(); row++){
        line_input = std::to_string((new_LDL->at(col))[row])+"\n";
        outFile << line_input;
      }
    }
    //Adding in the prev_LDL std::vector
    for(int col = 0; col < (signed int) prev_LDL->size(); col++){
      for(int row = 0; row < (signed int) (prev_LDL->at(col)).size(); row++){
        line_input = std::to_string((prev_LDL->at(col))[row])+"\n";
        outFile << line_input;
      }
    }
    //Adding the period information
    line_input = std::to_string(period)+"\n";
    outFile << line_input;
    outFile.close();
  }
}
