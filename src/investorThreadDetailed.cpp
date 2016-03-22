//in investorThread.cpp

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "investorThread.h"
#include "investorResultsFileName.h"
#include "restore_point.h"
#include "vec_functions.h"
#include "J.h"
#include "makeComparable.h"
#include "investor_data.h"
#include "import_export_text.h"


void investorThread(long double A, long double B, long double G, long double D, long double T, std::vector<std::vector<long double> >* Investordata_NaNfree, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double >* part, std::vector<std::vector<long double > >* disc, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, std::vector<std::vector<long double > >* Jvec, int first_look_index, long double missing, std::vector<std::vector<long double> >* Allfits, long double investor, int num_partitions, std::string delimit, std::string input_file_name, std::string sample, int z, std::vector<std::vector<long double > >* indexes, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct, std::string sys, std::string overWriteRestore, long double baseWealth, std::string checkPoint) {
  std::cout << "Investor: " << (int) investor << std::endl;
  std::cout << "Parameter Set: " << z << std::endl;
  std::cout << "Alpha: " << A << std::endl;
  std::cout << "Beta: " << B << std::endl;
  std::cout << "Gamma: " << G << std::endl;
  std::cout << "Delta: " << D << std::endl;
  std::cout << "Theta: " << T << std::endl;
  std::cout << "T Max: " << t_max->at(0) << std::endl;
  std::cout << "Partition: " << num_partitions << std::endl;
  
  //intializing all the objects
  long double period;
  std::vector<std::vector<long double > > new_LDL, prev_LDL;
  
  //Run period zero
  std::string restoreFile = investorResultsFileName(sys, sample, std::to_string((int) investor), std::to_string(num_partitions), input_file_name, std::to_string(z))+"-restore.txt";
  if (overWriteRestore=="F"){
    std::cout << "Trying to load the last retore point" << std::endl;
    //We want to start from the last check point
    if (getRestorePoint(restoreFile, &new_LDL, &prev_LDL, LDL_num_rows, LDL_num_cols, &period, checkPoint)) {
      //We were able to start from the last check point
      std::cout << "Running from last restore point" << std::endl;
      period = period + 1.0;
      while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
        prev_LDL = new_LDL;
        std::cout << "Starting period " << period << " ..." << std::endl;
        J(&new_LDL, LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, &prev_LDL, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
        period = period + 1.0;
      }
    }
    else {
      //Error, we weren't able to start from the last check point
      //start fresh
      period = 0.0;
      prev_LDL = new_LDL;
      std::cout << "Starting period " << period << " ..." << std::endl;
      J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
      period = period + 1.0;
      prev_LDL = new_LDL;
      std::cout << "Starting period " << period << " ..." << std::endl;
      J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
      period = period + 1.0;
      while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
        prev_LDL = new_LDL;
        std::cout << "Starting period " << period << " ..." << std::endl;
        J(&new_LDL, LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, &prev_LDL, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
        period = period + 1.0;
      }
    }
  }
  else{
    //We don't want to start from the last check point
    std::cout << "Running from the beginning" << std::endl;
    //start fresh
    period = 0.0;
    prev_LDL = new_LDL;
    std::cout << "Starting period " << period << " ..." << std::endl;
    J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
    period = period + 1.0;
    prev_LDL = new_LDL;
    std::cout << "Starting period " << period << " ..." << std::endl;
    J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
    period = period + 1.0;
    while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
      prev_LDL = new_LDL;
      std::cout << "Starting period " << period << " ..." << std::endl;
      J(&new_LDL, LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, &prev_LDL, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
      period = period + 1.0;
    }
  }
  
  //The first column added to the investor data by makeComparable is needed to find the predicted look decisions associated with each actual look decision
  /* *****************************************************************************
  Structure of Investordata_NaNfree at this point in the code:
  [0] Vector of investor IDs
  [1] Vector of look and don't look decisions
  [2] Vector of personal returns
  [3] Vector of continuous personal returns
  [4] Vector of continuous market returns
  ***************************************************************************** */
  makeComparable(Investordata_NaNfree, first_look_index, T, D, part, part->size(), t_max, indexes, missing, baseWealth); // add index column for fit/comparison
  
  /* *****************************************************************************
  Structure of Investordata_NaNfree at this point in the code:
  [0]  Vector of investor IDs
  [1]  Vector of look and don't look decisions
  [2]  Vector of personal returns
  [3]  Vector of continuous personal returns
  [4]  Vector of continuous market returns
  [5]  Vector of indexes meant to map element of state space to a trading day in the investor's history
  [6]  Vector of implied actual wealth values from investor's trading day statistics
  [7]  Vector of implied approx. wealth values from investor's trading day statistics
  [8]  Vector of implied benchmark values from investor's trading day statistics
  [9]  Vector of actual days since the investor last looked
  [10] Vector of implied wealth since the investor last looked
  ***************************************************************************** */
  
  long double fits = 0.0;
  int skip = 0;
  
  int ssIndexes; //indexes to map an element of the state space to a day
  for(int p = first_look_index+1; p <= (signed int) ((Investordata_NaNfree->at(0)).size()); p++) {
    ssIndexes = round(Investordata_NaNfree->at(5)[(p-1)]); //-1 adjusts for C++ vectors starting at index 0, not 1
    if ((Investordata_NaNfree->at(5)[(p-1)] == missing) | (Investordata_NaNfree->at(1)[(p-1)] == missing)) {
      skip = skip + 1;
    }
    else {
      fits = fits + pow((new_LDL[0][ssIndexes-1] - Investordata_NaNfree->at(1)[p-1]),2);
    }
  }
  
  fits = 1 - (fits/(Investordata_NaNfree->at(0).size()-first_look_index-skip));
  Allfits->at(0)[0] = investor;
  Allfits->at(1)[0] = A;
  Allfits->at(2)[0] = B;
  Allfits->at(3)[0] = G;
  Allfits->at(4)[0] = D;
  Allfits->at(5)[0] = T;
  Allfits->at(6)[0] = fits;
  std::cout << "Fit: " << fits << std::endl;
  
  /* *****************************************************************************
   Creating a matrix of data to extract
  ****************************************************************************** */
  int extraVars = 15;
  std::vector<std::vector<long double>* > extraData;
  extraData.resize(extraVars);
  //Add "actual" values
  extraData[0] = &(Investordata_NaNfree->at(1)); //look decisions
  extraData[1] = &(Investordata_NaNfree->at(3)); //personal return
  extraData[2] = &(Investordata_NaNfree->at(4)); //market return
  extraData[3] = &(Investordata_NaNfree->at(7)); //implied actual approx. wealth
  extraData[4] = &(Investordata_NaNfree->at(8)); //implied actual benchmark
  extraData[5] = &(Investordata_NaNfree->at(9)); //actual days since the investor last looked
  extraData[6] = &(Investordata_NaNfree->at(10)); //implied actual wealth since the investor last looked
  extraData[7] = &(Investordata_NaNfree->at(6)); //implied actual wealth
  //Add "predicted" values
  <std::vector<<std::vector<long double> > extraPredData;
  int extraVars2 = extraVars-8;
  extraPredData.resize(extraVars2);
  for(int k = 0; k < (extraVars2); k++){
    (extraPredData[k]).resize((Investordata_NaNfree->at(0)).size());
  }
  int w_n, b_n, t_n, wT_n;
  int nt = t_max->at(0);
  int np = part->size();
  for(int i = 0; i < ((signed int) ((Investordata_NaNfree->at(0)).size())); i++){
    ssIndexes = max(round((Investordata_NaNfree->at(5))[i]), (long double) 0.0); //investor row to LDL vector row convertor
    if (ssIndexes > 0) {
      w_n = ceil(ssIndexes/(1.0*np*nt*np));
      b_n = ceil(ssIndexes/(1.0*np*nt)) - (ceil(ssIndexes/(1.0*np*nt*np)) - 1.0)*np;
      t_n = ceil(ssIndexes/(1.0*np)) - (ceil(ssIndexes/(1.0*np*nt)) - 1.0)*nt;
      wT_n = ssIndexes - (w_n-1)*(np*nt*np) - (b_n - 1)*(np*nt) - (t_n - 1)*(np);
      extraPredData[0][i] = new_LDL[0][ssIndexes-1]; //look decisions
      extraPredData[1][i] = new_LDL[1][ssIndexes-1]; //utility from decision
      extraPredData[2][i] = new_LDL[2][ssIndexes-1]; //utility from alt. decision
      extraPredData[3][i] = part->at(w_n-1); //approx. wealth in state space
      extraPredData[4][i] = part->at(b_n-1); //benchmark state space
      extraPredData[5][i] = t_n; //time since last look in state space
      extraPredData[6][i] = part->at(wT_n-1); //wealth at time since last look in state space
    }
    else {
      for(int j = 0; j < extraVars2; j++){
        extraPredData[j][i] = missing;
      }
    }
  }
  //merging data
  for(int i = 8; i < extraVars; i++){
    extraData[i] = &(extraPredData[i-8]);
  }
  //Export matrix
  std::string pathExtraData = investorResultsFileName(sys, sample, std::to_string((int) investor), std::to_string(num_partitions), input_file_name, std::to_string(z))+".txt";
  textMatrixExport((extraData[0])->size(), pathExtraData, &extraData);  
  
  exportInvestorData(Allfits, investor, num_partitions, delimit, input_file_name, sample, z, sys);
}
