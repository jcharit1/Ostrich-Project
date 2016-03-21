//in restore_point.h

#ifndef RESTORE_POINT_H    
#define RESTORE_POINT_H

#include <string>
#include <vector>

bool getRestorePoint(std::string restoreFile, std::vector<std::vector<long double> >* new_LDL, std::vector<std::vector<long double> >* prev_LDL, long double LDL_num_rows, long double LDL_num_cols, long double* period, std::string checkPoint);
void createRestorePoint(std::string restoreFile, std::vector<std::vector<long double> >* new_LDL, std::vector<std::vector<long double> >* prev_LDL, long double period, std::string checkPoint);

#endif