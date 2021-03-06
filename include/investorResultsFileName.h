//in investorResultsFileName.h

#ifndef INVESTORRESULTSFILENAME_H    
#define INVESTORRESULTSFILENAME_H

#include <string>

std::string investorResultsFileName(std::string sys, std::string sample, std::string investor, std::string npart, std::string parameterSet, std::string zthread);
std::string investorResultsDirName(std::string sys, std::string investor, std::string zthread);
std::string investorDetailedResultsFileName(std::string sys, std::string sample, std::string investor, std::string npart, std::string parameterSet, std::string zthread);

#endif