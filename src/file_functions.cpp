//in file_functions.cpp

#include "file_functions.h"
#include <fstream>
#include <algorithm>
#include <sys/stat.h>

bool fileExist(std::string name) {
  std::ifstream f(name.c_str());
  if (f.good()) {
    f.close();
    return true;
  }
  else {
    f.close();
    return false;
  }
}

bool fileExistStat(const std::string& name) {
  struct stat buf;
  return (stat(name.c_str(), &buf) == 0);
}

long double countFileLines(std::string fileName) {
  std::ifstream inFile(fileName.c_str());
  long double numLines = 1.0*std::count(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>(), '\n');
  inFile.close();
  return numLines;
}
