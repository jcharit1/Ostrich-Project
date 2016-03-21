//in investorDataFileName.cpp

#include "investorDataFileName.h"

std::string investorDataFileName(std::string sys, std::string sample, std::string investor) {
  //Program to constructing the input file full name regardless of the system
  
  std::string fullFileName, baseDir;
  
  //determining the cluster group
  int cl_int = (stoi(investor) % 500);
  std::string cl = std::to_string(cl_int);
  
  //name of the file, system independent
  std::string fileName = sample+"sample"+investor;
  
  //the base directory
  if (sys == "AWSEBS"){
    //on the EBS-backed amazon servers
    baseDir = "/investorData/cluster/cluster"+cl;
  }
  if (sys == "AWSNOV"){
    //on the amazon servers with no volumes
    baseDir = "/home";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    baseDir = "/user/user1/jc4144/Nachum/Ostrich/cluster/cluster"+cl;
  }
  
  fullFileName = baseDir+"/"+fileName;
  
  return fullFileName;
}