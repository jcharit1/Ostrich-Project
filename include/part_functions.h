//in part_functions.h 

#ifndef PART_FUNCTIONS_H    
#define PART_FUNCTIONS_H

#include <vector>

void makePart(std::vector<long double>* bin, long double first, int division, long double last);
void fillPart(std::vector<long double>* bin, long double start, long double steps, int num_steps);

#endif
