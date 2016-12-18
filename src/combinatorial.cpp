//in combinatorial.cpp

#include "combinatorial.h"
#include <iostream>
#include <math.h>

long double factorial(int n){
  if (n < 0) {
    return NAN;
  }
  if (n == 0) {
    return 1.0;
  }
  else{
    long double fact = 1.0;
    for(int i = 1; i <= n; i++){
      fact = fact*i*1.0;
    }
    return fact;
  }
}

long double nChoosek(int n, int k){
  long double x = factorial(n)/(factorial(k)*factorial(n-k));
  return x;
}