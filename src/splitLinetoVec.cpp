//in splitLinetoVec.cpp

#include "splitLinetoVec.h"
#include <math.h>

void splitLinetoVec(std::string line, std::vector<long double>* Vec, char delim){
  int pos = line.find(delim);
  int initialPos = 0;
  Vec->clear();
  
  // Decompose statement
  //(unsigned int) <- adding the following would remove a warning but cause failure
  while( pos != std::string::npos) {
    Vec->push_back(strtold((line.substr(initialPos, pos - initialPos)).c_str(), NULL));
    initialPos = pos + 1;
    
    pos = line.find(delim, initialPos);
  }
  
  // Add the last one
  int l_size = line.size();
  Vec->push_back(strtold((line.substr(initialPos, std::min(pos, l_size) - initialPos)).c_str(), NULL));
  
}