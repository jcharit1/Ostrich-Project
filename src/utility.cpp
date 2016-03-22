//in utility.cpp

#include "utility.h"

long double utility_look(long double wealth, long double benchmark, long double A, long double G){
  long double u;
  
  if(wealth >= benchmark){ 
    u = (1.0+A)*(wealth - benchmark);
  }
  else{
    u = G*(1.0+A)*(wealth - benchmark);
  }
  
  return u;
}

long double utility_dont_look(long double wealth, long double benchmark, long double G){
  long double u;
  
  if(wealth >= benchmark){ 
    u = (wealth - benchmark);
  }
  else{
    u = G*(wealth - benchmark);
  }  
  
  return u;
}

long double update_benchmark(long double wealth, long double benchmark, long double T_D){
  return T_D*(wealth) + (1.0-T_D)*(benchmark); //D if look, T otherwise
}