//in part_functions.cpp

#include "part_functions.h"

void makePart(std::vector<long double>* bin, long double first, int division, long double last){
  bin->resize(division); //avoids inefficient push_back calls
  bin->at(0) = first;
  long double split = division - 1.0;
  long double step = (last - first)/(split);
  for(int i = 1; i <= (int) split; i++){
    bin->at(i) = bin->at(i-1)+step;
  }
}

void fillPart(std::vector<long double>* bin, long double start, long double steps, int num_steps){
  bin->push_back(start);
  for(int i = 0; i < num_steps-1; i++){
    bin->push_back(steps+bin->at(i)); // b/c we preload bin w/ start and are pushing into bin, bin->at(i) reps the prior value
  }
}
