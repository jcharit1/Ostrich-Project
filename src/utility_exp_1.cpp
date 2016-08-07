//in utility_exp_1.cpp

#include "utility.h"
#include <math.h>

long double utility_look(long double wealth, long double benchmark, long double A, long double G){
  long double u;
  
  if(wealth >= benchmark){ 
    u = exp((1.0+A)*(wealth - benchmark))-1.0;
  }
  else{
    u = -1.0*exp(-1.0*G*(1.0+A)*(wealth - benchmark))+1.0;
  }
  
  return u;
}

long double utility_dont_look(long double wealth, long double benchmark, long double G){
  long double u;
  
  if(wealth >= benchmark){ 
    u = exp(wealth - benchmark)-1.0;
  }
  else{
    u = -1.0*exp(-1.0*G*(wealth - benchmark))+1.0;
  }  
  
  return u;
}

long double update_benchmark(long double wealth, long double benchmark, long double T_D){
  return T_D*(wealth) + (1.0-T_D)*(benchmark); //D if look, T otherwise
}