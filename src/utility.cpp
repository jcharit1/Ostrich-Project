//in utility.cpp

#include "utility.h"

long double utility(long double actual_wealth, long double benchmark, long double A, long double G){
  long double u;
  
  if(actual_wealth >= benchmark){ 
    u = (1.0+A)*(actual_wealth - benchmark);
  }
  else{
    u = G*(1.0+A)*(actual_wealth - benchmark);
  }
  
  return u;
}