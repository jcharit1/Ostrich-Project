//in vec_stat.h
//header file for vector statistics functions

#ifndef VEC_STAT_H    
#define VEC_STAT_H

#include <vector>

long double sumVec(std::vector<long double>* vec);
long double meanVec(std::vector<long double>* vec);
long double varVec(std::vector<long double>* vec, long double n);
void covMat(std::vector<std::vector<long double> >* cov_matrix, std::vector<long double>* v1, std::vector<long double>* v2, long double n);

#endif