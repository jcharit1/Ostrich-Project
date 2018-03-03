//in file_functions.h

#ifndef FILE_FUNCTIONS_H    
#define FILE_FUNCTIONS_H

#include <string>

bool fileExist(std::string name);
bool fileExistStat(const std::string& name);
long double countFileLines(std::string fileName);

#endif
