//in J.h
//the riemann sum variant of the J() function

#ifndef J_FUNCTION_H    
#define J_FUNCTION_H

#include <vector>
#include <string>

void J(std::vector<std::vector<long double> >* new_LDL, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double>* part, int part_size, std::vector<std::vector<long double> >* disc, int disc_size, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, long double A, long double B, long double G, long double D, long double T, long double period, std::vector<std::vector<long double > >* Jvec, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct);

#endif
