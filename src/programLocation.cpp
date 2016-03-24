//in programLocation.cpp

#include "programLocation.h"
#include <stdlib.h>

std::string programLocation(std::string programName, std::string sys) {
  //Program to constructing the program file full name regardless of the system
  
  std::string fullFileName, baseDir;
  
  //the base directory
  if (sys == "AWSEBS"){
    //on the EBS-backed amazon servers
    baseDir = "/main/code/bin";
  }
  if (sys == "AWSNOV"){
    //on the amazon servers with no volumes
    baseDir = "/home/bin";
  }
  if (sys == "CBS"){
    //on the Columbia B-school servers
    baseDir = "/user/user1/jc4144/Nachum/Ostrich/code/bin";
  }
  if (sys == "Personal"){
    //on Personal Laptop
    baseDir = "/home/jim/Dropbox/Nachum/OstrichCPP/AWSCode/Ostrich/code/bin";
  }
  if (sys == "Test"){
    //running test
    baseDir = ".";
  }
  
  fullFileName = baseDir+"/"+programName;
  
  return fullFileName;
}

std::string getProgramName(std::string programOneVersion, std::string beta){
  std::string programName;
  
  long double BETA = strtold(beta.c_str(), NULL);
  
  if(BETA==0 and programOneVersion=="Simple"){
    programName = "ProgramOneFinalRSB0";
  }
  if(BETA==0 and programOneVersion=="Detailed"){
    programName = "ProgramOneFinalRSB0_Detailed";
  }
  if(BETA!=0 and programOneVersion=="Simple"){
    programName = "ProgramOneFinalRS";
  }
  if(BETA!=0 and programOneVersion=="Detailed"){
    programName = "ProgramOneFinalRS_Detailed";
  }
  
  return programName;
}