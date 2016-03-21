// in ParentOstrich.cpp

#include "investorListFileName.h"
#include "import_export_text.h" 
#include "import_para.h"
#include "programLocation.h"
#include "investorDataFileName.h"
#include "text_import_text.h"
#include "file_functions.h"
#include "investorResultsFileName.h"
#include "SGE.h"
#include <string> 
#include <vector>

int main(int argc, char *argv[]){
  /*
  Program designed to call ProgramOneFullIndep for each investor and element of the
  parameter space as a separate process
  Input 1: file path for the parameters, it should be parameters/mypara.txt
  Input 2: name for that set of parameters, will be appended to the output name
  Input 3: same of investors to use
  */
  
  //Dataset inputs
  std::string programOneVersion = argv[1];
  std::string parameter_file_path = argv[2];
  std::string input_file_name = argv[3]; //name of the parameter for the output
  std::string sample = argv[4]; //for the investor data file
  std::string row = argv[5]; //the number of rows in the data file
  std::string inv_set = argv[6]; //name of the investor set file
  std::string inv_set_size = argv[7]; //number of investors in that set file
  
  //Inputs for the Monte Carlo Simulations or Riemann approximation
  std::string EUType_str = argv[8]; //method for estimating the expected utility -- MC: Monte Carlo, RS: Riemann Sum
  std::string MCNum_str = argv[9]; //# of draws for Monte Carlo simulation
  std::string alpha_CI_str = argv[10]; //1-alpha_CI is the percent of mass under the actual wealth distribution that we would like to attempt to estimate with Riemann sum
  std::string error_pct_str = argv[11]; //the error tolerance for the Riemann sum approximation
  
  //Input: system information
  std::string sys = argv[12]; //server type
  
  //Replace existing results files?
  std::string writeOverResults = argv[13];
  
  //Dealing with restore files
  std::string checkPoint = argv[14]; //T or F, make restore files?
  std::string overWriteRestore = argv[15]; //T or F, ignore restore points and start from scratch
  
  //Creating the std::vector of investor IDs
  int max_row = atoi(inv_set_size.c_str());
  std::vector<std::string> investorList(max_row, ".");
  std::string investorListFilePath = investorListFileName(sys, inv_set)+".txt";
  textImportText(max_row, investorListFilePath, &investorList);
  
  //the system commands returns ints, this catches them to avoid a compiling warning
  int catchSysCommand;
  
  //Creating the parameter vectors
  //I create them as LDs even though I translated them into strings later
  std::vector<std::string> alpha;
  std::vector<std::string> beta;
  std::vector<std::string> gamma;
  std::vector<std::string> delta;
  std::vector<std::string> theta;
  std::vector<std::string> t_max;
  std::vector<std::string> npart;
  std::vector< std::vector<std::string>*> inputVec = {&alpha, &beta, &gamma, &delta, &theta, &t_max, &npart};
  importPara(parameter_file_path ,&inputVec);
  
  //get the memory request for the SGE commands
  std::string memRequest = getMemRequest(programOneVersion, &npart, MCNum_str, sys);
  
  //get the SGE commands
  std::vector<std::string> comVec = {".", "."};
  getSGECom(sys, &comVec, memRequest);
  std::string sgeLeadingCom = comVec[0];
  std::string sgeEndingCom = comVec[1];
  
  //the investor data file to check if it has already completed
  std::string investorResultsFile;
  //hold the sys commands
  std::string command_str;
  
  //Full file path of the Program
  std::string programPath = programLocation(programOneVersion, sys);
  
  //looping over investors
  for(int i = 0; i < (signed int) investorList.size(); i++){
    std::string investor = investorList.at(i);
    std::string investorDataFile = investorDataFileName(sys, sample, investor)+".txt";
    int z = 1;
    //loopingover parameters
    for(int a = 0; a< (signed int) alpha.size(); a++){
      for(int b = 0; b< (signed int) beta.size(); b++){
        for(int g = 0; g< (signed int) gamma.size(); g++){
          for(int d = 0; d< (signed int) delta.size(); d++){
            for(int t = 0; t< (signed int) theta.size(); t++){
              for(int tm = 0; tm< (signed int) t_max.size(); tm++){
                for(int np = 0; np< (signed int) npart.size(); np++){
                  std::string A = alpha[a];
                  std::string B = beta[b];
                  std::string G = gamma[g];
                  std::string D = delta[d];
                  std::string T = theta[t];
                  std::string TM = t_max[tm];
                  std::string NP = npart[np];
                  //checking if results already exists
                  investorResultsFile = investorResultsFileName(sys, sample, investor, NP, input_file_name, std::to_string(z))+".txt";
                  if ((fileExist(investorResultsFile)==false) or (writeOverResults == "T")){
                    //results file doesn't exist or I want to write over all results, run the file
                    //run only one set of parameters or it might override files with different results
                    command_str = sgeLeadingCom+programPath+char(32)+investorDataFile+" "+sample+" "+row+" "+input_file_name+" "+A+" "+B+" "+G+" "+D+" "+T+" "+TM+" "+NP+" "+std::to_string(z)+" "+EUType_str+" "+MCNum_str+" "+alpha_CI_str+" "+error_pct_str+" "+sys+" "+checkPoint+" "+overWriteRestore+sgeEndingCom;
                    catchSysCommand = system(command_str.c_str());
                  }
                  z = z + 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}