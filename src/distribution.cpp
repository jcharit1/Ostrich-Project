//in distribution.cpp
//header file for vector statistics functions

#include "distribution.h"
#include <math.h>

long double lognorm_pdf(long double x, long double m, long double v){
  long double pi = M_PI;
  long double lnx = log(x);
  long double s = sqrt(v); //std dev.
  
  long double pr1 = ((1.0)/(x*sqrt(2.0*pi)*s));
  long double pr2 = -1.0*(pow(lnx - m,2.0)/(2.0*v));
  long double pr = pr1*exp(pr2);
  
  return pr;
}

long double stdNormInv(long double p) {
  /* Inverse normal CDF
  Source: http://home.online.no/~pjacklam/notes/invnorm/impl/natarajan/normsinv.h
  Main Page: http://home.online.no/~pjacklam/notes/invnorm/#C
  Author: V. Natarajan (Kanchipuram (near Madras), India)
  */
  
  /* Needed constants*/
  long double P_LOW = 0.02425;
  long double P_HIGH = 1.0 - P_LOW;
  
  long double A1 = (-3.969683028665376e+01);
  long double A2 = 2.209460984245205e+02;
  long double A3 = (-2.759285104469687e+02);
  long double A4 = 1.383577518672690e+02;
  long double A5 = (-3.066479806614716e+01);
  long double A6 = 2.506628277459239e+00;
  
  long double B1 = (-5.447609879822406e+01);
  long double B2 = 1.615858368580409e+02;
  long double B3 = (-1.556989798598866e+02);
  long double B4 = 6.680131188771972e+01;
  long double B5 = (-1.328068155288572e+01);
  
  long double C1 = (-7.784894002430293e-03);
  long double C2 = (-3.223964580411365e-01);
  long double C3 = (-2.400758277161838e+00);
  long double C4 = (-2.549732539343734e+00);
  long double C5 = 4.374664141464968e+00;
  long double C6 = 2.938163982698783e+00;
  
  long double D1 = 7.784695709041462e-03;
  long double D2 = 3.224671290700398e-01;
  long double D3 = 2.445134137142996e+00;
  long double D4 = 3.754408661907416e+00;
  
  /* Initializing constants*/
  long double x;
  long double q, r, u, e;
  
  if ((0.0 < p )  && (p < P_LOW)){
    q = sqrt(-2*log(p));
    x = (((((C1*q+C2)*q+C3)*q+C4)*q+C5)*q+C6) / ((((D1*q+D2)*q+D3)*q+D4)*q+1.0);
  }
  else {
    if ((P_LOW <= p) && (p <= P_HIGH)){
      q = p - 0.5;
      r = q*q;
      x = (((((A1*r+A2)*r+A3)*r+A4)*r+A5)*r+A6)*q /(((((B1*r+B2)*r+B3)*r+B4)*r+B5)*r+1.0);
    }
    else {
      if ((P_HIGH < p)&&(p < 1.0)){
        q = sqrt(-2.0*log(1.0-p));
        x = -1.0*(((((C1*q+C2)*q+C3)*q+C4)*q+C5)*q+C6) / ((((D1*q+D2)*q+D3)*q+D4)*q+1.0);
      }
    }
  }
  
  if(( 0.0 < p)&&(p < 1.0)){
    e = 0.5 * erfc(-1.0*x/sqrt(2.0)) - p;
    u = e * sqrt(2*M_PI) * exp(x*x/2.0);
    x = x - u/(1.0 + x*u/2.0);
  }
  return x;
}

long double logNormInvCDF(long double p, long double m, long double v){
  /* Inverse lognormal CDF
   See: http://en.wikipedia.org/wiki/Log-normal_distribution#Cumulative_distribution_function
   */
  
  long double s = sqrt(v); //std dev.
  
  //Use the inv std norm
  long double x = stdNormInv(p);
  long double logx = exp(s*x+m);
  return logx;
}

long double logNormCDF(long double x, long double m, long double v){
  /* lognormal CDF
   See: http://en.wikipedia.org/wiki/Log-normal_distribution#Cumulative_distribution_function
   */
  
  long double s = sqrt(v); //std dev.
  long double pvalue = (0.5)*erfc(-1.0*((log(x)-m)/(s*sqrt(2))));
  return pvalue;
}