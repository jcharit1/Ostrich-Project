//in investorThreadFunction.h

#ifndef INVESTORTHREADFUNCTION_H    
#define INVESTORTHREADFUNCTION_H

#include <vector>
#include <string>

long double investorThreadFunction(long double A, long double B, long double G, long double D, long double T, std::vector<std::vector<long double> >* Investordata_NaNfree, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double >* part, std::vector<std::vector<long double > >* disc, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, std::vector<std::vector<long double > >* Jvec, int first_look_index, long double missing, long double investor, int num_partitions, std::string delimit, std::vector<std::vector<long double > >* indexes, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct, long double baseWealth);

#endif