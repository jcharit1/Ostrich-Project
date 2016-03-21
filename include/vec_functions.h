//in vec_functions.h

#ifndef VEC_FUNCTIONS_H    
#define VEC_FUNCTIONS_H

#include <vector>

void replaceMissing(std::vector<std::vector<long double> >* newVec, std::vector<std::vector<std::vector<long double> > >* oldVec, long double missing, int investor, int flag, long double replacement);
bool isEqual(std::vector<long double>* v1,std::vector<long double>* v2);
int findInLDVector(std::vector<long double>* vec, long double n);
int countInLDVec(std::vector<long double>* vec, long double n);

#endif