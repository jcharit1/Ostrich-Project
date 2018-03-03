//in OstrichFunction.h

#ifndef OSTRICHFUNCTION_H    
#define OSTRICHFUNCTION_H

#include <string>

long double OstrichFunction(std::string file_path, int max_row, long double A, long double B, long double G, long double D, long double T, long double T_Max, long double npart, long double MCNum, std::string EUType_str, long double alpha_CI, long double error_pct);
  
#endif