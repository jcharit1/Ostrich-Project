//in vec_functions.cpp

#include "vec_functions.h"
#include <iostream>

void replaceMissing(std::vector<std::vector<long double> >* newVec, std::vector<std::vector<std::vector<long double> > >* oldVec, long double missing, int investor, int flag, long double replacement) {
  if (flag == 1 or flag == 0) {
    if (flag == 1){
      for(int k = 0; k <  (signed int) ((oldVec->at(investor))[1]).size(); k++){ //int investor is the index that return's the investor's data
        //k is the length of the look or don't look column
        for( int j = 0; j < (signed int) (oldVec->at(investor)).size(); j++) {
          //j is the number of columns of data for each investor
          if ((j == 1) & ((oldVec->at(investor))[j][k] == missing)){ //j==1 is the look/notLook column
            (newVec->at(j)).push_back(replacement); //replacing the missing look/notLook values
          }
          else {
            (newVec->at(j)).push_back((oldVec->at(investor))[j][k]); //copying the rest, prob. can do this by pushing the whole std::vector
          }
        }
      }
    }
    else {
      //Checking for missing look/not look decisions (cols=[i][1]) from the current investor i
      // for investor data variable j, in observation k
      for(int k = 0; k < (signed int) ((oldVec->at(investor))[0]).size(); k++){
        for(int j = 0; j < (signed int) (oldVec->at(investor)).size(); j++){
          //one refers to the look not look decision
          if((oldVec->at(investor))[1][k] != missing){
            //only copying over rows with non-missing look/notLook decision
            (newVec->at(j)).push_back((oldVec->at(investor))[j][k]);
          }
        }
      }
    }
  }
}

bool isEqual(std::vector<long double>* v1,std::vector<long double>* v2){
  if(v1->size() != v2->size()){
    return false;
  }
  for(int i = 0; i< (signed int) v1->size(); i++){
    if(v1->at(i) != v2->at(i)){
      return false;
    }
  }
  return true;
}

int findInLDVector(std::vector<long double>* vec, long double n) {
  for(int i =0; i< (signed int) vec->size(); i++){
    if(vec->at(i)== n){
      return i+1;
    }
  }
  return 0;
}

int countInLDVec(std::vector<long double>* vec, long double n){
  
  int cnt = 0;
  for(int i =0; i< (signed int) vec->size(); i++){
    if(vec->at(i)== n){
      cnt = cnt+1; //counting how often we find n
    }
  }
  return cnt;
}