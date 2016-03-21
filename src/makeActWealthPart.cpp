//in makeActWealthPart.cpp

#include "makeActWealthPart.h"
#include "part_functions.h"
#include "distribution.h"
#include <vector>
#include <math.h>

void makeActWealthPart(long double m, long double v, long double alpha_CI, long double error_pct, std::vector<long double>* part){
  /* Function to make a partition of the actual wealth distribution
  alpha_CI: the alpha that determines the interval we will partition and estimate with Riemann
  error_pct: error of the Riemann approximate as a percent of the mass of the distribution
  
  Riemann error estimate function from: http://www.math.uh.edu/~jiwenhe/Math1432/lectures/lecture11_handout.pdf
  We determine the number of partitions, n, by solving for two equations:
  (1) riemann_error <= ((b-a)/n)*(f(b)-f(a)), where [a, b] are the min and max values of the partition, f() is the actual wealth distribution, and n is the number of partitions
  (2) riemann_error_tolerance = rieman_error/CDF(partition), where CDF(partition) is the CDF of the region of the distribution that is being partitioned
  */
  
  //First determine the mode, we will use a Riemann error bound, so we need to "cut" the distribution into
  //monotone (non-decreasing) pieces
  long double mode = exp(m - v);
  long double p_mode = lognorm_pdf(mode, m, v);
  long double modeCDF = logNormCDF(mode, m, v); //CDF @ mode, needed for next steps
  
  //Now determine the interval [a, b] we will partition and estimate with Riemann
  long double p_a = (alpha_CI/2.0);
  long double a = logNormInvCDF(p_a, m, v);
  long double p_b = 1.0-p_a;
  long double b = logNormInvCDF(p_b, m, v);
  
  //Mass under the halves
  long double AmodeCDF = modeCDF - logNormCDF(a, m, v); //from A to Mode
  long double modeBCDF = logNormCDF(b, m, v) - modeCDF; //from Mode to B
  
  //Initializing variables for the partition step
  int N_right, N_left, N;
  
  if ((a < mode) and (b > mode)){
    //if the mode is at the center of our partitions: [a, mode, b]
    //Now determine the number of cuts to bound our error to error_pct percent of the mass
    N_right = round(((mode-a)/(error_pct*AmodeCDF))*(p_mode - p_a));
    N_left = round(((b-mode)/(error_pct*modeBCDF))*(p_mode - p_b));
    
    //Stuff the overall partition
    part->resize(N_right+N_left-1); //avoid calling push_back too much
    part->at(0) = a;
    for(int i = 1; i < N_right; i++){
      part->at(i) = part->at(i-1)+((mode - a)/(1.0*N_right - 1.0));
    }
    for(int i = N_right; i < (N_right+N_left-1); i++){
      part->at(i) = part->at(i-1)+((b - mode)/(1.0*N_left - 1.0));
    }
  }
  else if ((mode <= a)){
    //if the the mode is to the right of our lower bound: [mode, a, b]
    N = round(((b-mode)/(error_pct*modeBCDF))*(p_b - p_mode));
    makePart(part, mode, N, b);
  }
  else /*((mode >= b))*/{
    //if the the mode is to the left of our upper bound: [a, b, mode]
    N = round(((mode-a)/(error_pct*AmodeCDF))*(p_mode - p_a));
    makePart(part, a, N, mode);
  }
}
