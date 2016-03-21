//in vec_stat.cpp
//cpp file for vector statistics functions

#include "vec_stat.h"
#include <iostream>
#include <math.h>


long double sumVec(std::vector<long double>* vec){
  long double sum = 0.0;
  for(int i =0; i< (signed int) vec->size(); i++){
    sum = sum + (vec->at(i));
  }
  return sum;
}

long double meanVec(std::vector<long double>* vec){
  long double mean = ((sumVec(vec)*1.0)/(vec->size()));
  return mean;
}

long double varVec(std::vector<long double>* vec, long double n){
  long double mean = meanVec(vec);
  long double sum = 0.0;
  
  for(int i =0; i< (signed int) vec->size(); i++){
    sum = sum + pow(((vec->at(i))-mean),2.0); //taking ^2 directly threw an error
  }
  
  long double N = (vec->size()) - n;
  long double var = sum*(1.0/N);
  return var;
}

void covMat(std::vector<std::vector<long double> >* cov_matrix, std::vector<long double>* v1, std::vector<long double>* v2, long double n){
  if(v1->size() != v2->size()){
    std::cout << "Error, can't calculate the covar matrix, std::vectors are not the same size" << std::endl;
  }
  
  //Note assumes cov_matrix is a 2x2 matrix
  long double varv1 = varVec(v1, 1.0);
  long double varv2 = varVec(v2, 1.0);
  long double meanv1 = meanVec(v1);
  long double meanv2 = meanVec(v2);
  long double sum = 0.0;
  
  for(int i =0; i< (signed int) v1->size(); i++){
    sum = sum + ((v1->at(i))-meanv1)*((v2->at(i))-meanv2); //taking ^2 directly threw an error
  }
  
  long double N = (v1->size()) - n*1.0;
  long double cov12 = sum*(1.0/N);
  (cov_matrix->at(0)).push_back(varv1);
  (cov_matrix->at(0)).push_back(cov12);
  (cov_matrix->at(1)).push_back(cov12);
  (cov_matrix->at(1)).push_back(varv2);
  /*
   cov_matrix:
   |varv1 | cov12|
   |cov12 | varv2|
   */
} 
