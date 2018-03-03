//in investor_data.h

#ifndef INVESTOR_DATA_H    
#define INVESTOR_DATA_H

#include <vector>
#include <string>

void importInvestorData(int max_row, std::string file_path, std::vector<std::vector<long double>* >* data);
void exportInvestorData(std::vector<std::vector<long double> >* allfits, long double investor, int num_partitions, std::string delimit, std::string input_file_name, std::string sample, int z, std::string sys);
void getInvestorData(std::vector<std::vector<long double>* >* all_data, std::vector<long double>* investor_ids, std::vector<std::vector<long double> >* investor_data, std::vector<std::vector<std::vector<long double> > >* investor_all);

#endif