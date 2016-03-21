//in distribution.h
//header file for distribution fuctions

#ifndef DISTRIBUTION_H    
#define DISTRIBUTION_H

long double stdNormInv(long double p);
long double lognorm_pdf(long double x, long double m, long double v);
long double logNormCDF(long double x, long double m, long double v);
long double logNormInvCDF(long double p, long double m, long double v);

#endif