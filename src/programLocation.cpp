//in programLocation.cpp

#include "programLocation.h"

std::string programLocation(std::string programName, std::string sys) {
  //Program to constructing the program file full name regardless of the system
  
  std::string fullFileName, baseDir;
  
  //the base directory
  if (sys == "AWSEBS"){
    //on the EBS-backed amazon servers
    baseDir = "/main/code";
  }
  if (sys == "AWSNOV"){
    //on the amazon servers with no volumes
    baseDir = "/home";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    baseDir = "/user/user1/jc4144/Nachum/Ostrich";
  }
  
  fullFileName = baseDir+"/"+programName;
  
  return fullFileName;
}