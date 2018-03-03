//in NDiscrete.cpp

#include "NDiscrete.h"
#include "combinatorial.h"
#include <vector>
#include <math.h>


void NDiscrete(std::vector<std::vector<long double> >* bin, long double mean, long double stdDev, int num_disc){
  // Creates discrete approximation of a normal distribution using binomial
  // approximation.
  long double up = exp(stdDev*sqrt(1.0/num_disc));
  long double down = 1.0/up;
  long double p_up = (exp(mean*(1.0/num_disc)) - down)/(1.0*(up - down));
  long double p_down = 1.0 - p_up;
  
  //BINOMIAL APPROXIMATION
  std::vector<long double> zeros((num_disc+1), 0);
  bin->push_back(zeros);
  bin->push_back(zeros);
  
  for(int x = 0; x <= num_disc; x++){
    (bin->at(0))[(x-1)+1] = (pow(up,1.0*(num_disc-x))*pow(down,1.0*x))-1.0;
    (bin->at(1))[(x-1)+1] = nChoosek(num_disc,num_disc-x)*pow(p_up, 1.0*(num_disc-x))*pow(p_down,1.0*x);  // prob
  }
}
