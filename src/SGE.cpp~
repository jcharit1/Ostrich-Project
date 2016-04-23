//in SGE.cpp

#include "SGE.h"

std::string getMemRequest(std::string programOneVersion, std::vector<std::string>* npart, std::string MCNum_str, std::string sys){
  /*
  Function to determine the appropriate memory request by the input parameters and the system used
  */
  
  std::string memRequest = "5G";
  
  //First determine the max state space partition requested
  int maxNPart = atoi((npart->at(0)).c_str());
  int candidateMaxNPart;
  for(int i = 1; i < (signed int) npart->size(); i++){
    candidateMaxNPart = atoi((npart->at(i)).c_str());
    if (maxNPart < candidateMaxNPart) {
      maxNPart = candidateMaxNPart;
    }
  }
  
  //Now determine the memory request by system
  if (programOneVersion == "ProgramOneFinalRS" or programOneVersion == "ProgramOneFinalRS_Detailed"){
    if (sys == "CBS"){
      if (maxNPart <= 100){
        memRequest = "2G";
      }
      if ((maxNPart > 100) & (maxNPart <= 200)){
        memRequest = "5G";
      }
      if ((maxNPart > 200) & (maxNPart <= 300)){
        memRequest = "6G";
      }
    }
  }
  
  return memRequest;
}

void getSGECom(std::string sys, std::vector<std::string>* comVec, std::string memRequest) {
  /*
   Returns the leading and ending commands for sge
   */
  std::string leadingCom, endingCom;
  if ((sys == "AWSEBS") | (sys == "AWSNOV")){
    //on the EBS-backed amazon servers
    leadingCom = "qsub -V -b y -cwd -N \"ProgramOne\" -o /dev/null -e /dev/null \"ulimit -c 0; ";
    endingCom = "\" \n";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    leadingCom = "/apps/wrappers/sge_run --grid_quiet --grid_submit=batch --grid_mem="+memRequest+" \"ulimit -c 0; ";
    endingCom = "\" \n";
  }
  comVec->at(0) = leadingCom;
  comVec->at(1) = endingCom;
}
