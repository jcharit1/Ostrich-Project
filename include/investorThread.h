//in investorThread.h

#ifndef INVESTOR_THREAD_H    
#define INVESTOR_THREAD_H

#include <vector>
#include <string>

void investorThread(long double A, long double B, long double G, long double D, long double T, std::vector<std::vector<long double> >* Investordata_NaNfree, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double >* part, std::vector<std::vector<long double > >* disc, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, std::vector<std::vector<long double > >* Jvec, int first_look_index, long double missing, std::vector<std::vector<long double> >* Allfits, long double investor, int num_partitions, std::string delimit, std::string input_file_name, std::string sample, int z, std::vector<std::vector<long double > >* indexes, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct, std::string sys, std::string overWriteRestore, long double baseWealth, std::string checkPoint);

#endif