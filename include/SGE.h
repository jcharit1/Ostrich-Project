//in SGE.h

#ifndef SGE_H    
#define SGE_H

#include <vector>
#include <string>

std::string getMemRequest(std::string programOneVersion, std::vector<std::string>* npart, std::string MCNum_str, std::string sys);
void getSGECom(std::string sys, std::string investor, std::string zthread, std::vector<std::string>* comVec, std::string memRequest, std::string gen_error_out_files);
  
#endif
