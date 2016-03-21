//in makeComparable.h

#ifndef MAKE_COMPARABLE_H    
#define MAKE_COMPARABLE_H

#include <vector>

void makeComparable(std::vector<std::vector<long double> >* investor_data, int first_look_index, long double T, long double D, std::vector<long double>* part, int part_size, std::vector<long double>* t_max, std::vector<std::vector<long double > >* indexes, long double missing, long double baseWealth);

#endif