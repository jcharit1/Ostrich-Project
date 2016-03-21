//in investorListFileName.cpp

#include "investorListFileName.h"

std::string investorListFileName(std::string sys, std::string listTag) {
  //Program to constructing the investor list file full name regardless of the system
  
  std::string fullFileName, baseDir;
  
  //name of the file, system independent
  std::string fileName = listTag+"sampleID";
  
  //the base directory
  if (sys == "AWSEBS"){
    //on the EBS-backed amazon servers
    baseDir = "/main/investorLists";
  }
  if (sys == "AWSNOV"){
    //on the amazon servers with no volumes
    baseDir = "/home";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    baseDir = "/user/user1/jc4144/Nachum/Ostrich";
  }
  
  fullFileName = baseDir+"/"+fileName;
  
  return fullFileName;
}