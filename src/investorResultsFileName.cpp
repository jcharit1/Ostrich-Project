//in investorResultsFileName.cpp

#include "investorResultsFileName.h"

std::string investorResultsFileName(std::string sys, std::string sample, std::string investor, std::string npart, std::string parameterSet, std::string zthread) {
  //Program to constructing the output file full name regardless of the system
  int catchSysCommand;
  std::string fullFileName, baseDir;
  
  //determining the cluster group
  int cl_int = (stoi(investor) % 500);
  std::string cl = std::to_string(cl_int);
  
  //name of the file, system independent
  std::string fileName = sample+"id_"+investor+"_fitness_N"+npart+"-"+parameterSet+"_"+zthread;
  
  //the base directory
  if (sys == "AWSEBS"){
    //on the EBS-backed amazon servers
    baseDir = "/investorOutput/cluster/cluster"+cl+"/thread"+zthread;
    
    //making sure the folders exits, there is a problem with the volume
    std::string dirCommand1 = "cd /investorOutput/cluster; mkdir cluster"+cl;
    std::string dirCommand2 = "cd /investorOutput/cluster/cluster"+cl+"; mkdir thread"+zthread;
    catchSysCommand = system(dirCommand1.c_str());
    catchSysCommand = system(dirCommand2.c_str());
  }
  if (sys == "AWSNOV"){
    //on the amazon servers with no volumes
    baseDir = "/home";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    baseDir = "/NOBACKUP/scratch/jc4144/Nachum/Ostrich/cluster/cluster"+cl+"/thread"+zthread;
  }
  
  fullFileName = baseDir+"/"+fileName;
  
  return fullFileName;
}
