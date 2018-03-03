// in splitLinetoStringVec.cpp

#include "splitLinetoStringVec.h"
#include <algorithm>

void splitLinetoStringVec(std::string line, std::vector<std::string>* Vec, char delim){
  int pos = line.find(delim);
  int initialPos = 0;
  Vec->clear();
  std::string catcher;
  
  // Decompose statement
  //(unsigned int) <- adding the following would remove a warning but cause failure
  while( pos != std::string::npos) {
    catcher = line.substr(initialPos, pos - initialPos);
    Vec->push_back(catcher);
    initialPos = pos + 1;
    
    pos = line.find(delim, initialPos);
  }
  
  // Add the last one
  int l_size = line.size();
  catcher = line.substr(initialPos, std::min(pos, l_size) - initialPos);
  Vec->push_back(catcher);
}