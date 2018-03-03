//in utility.h

#ifndef UTILITY_H    
#define UTILITY_H

long double utility_look(long double wealth, long double benchmark, long double A, long double G);
long double utility_dont_look(long double wealth, long double benchmark, long double G);
long double update_benchmark(long double wealth, long double benchmark, long double T_D);

#endif