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


void investorThread(long double A, long double B, long double G, long double D, long double T, std::vector<std::vector<long double> >* Investordata_NaNfree, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double >* part, std::vector<std::vector<long double > >* disc, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, std::vector<std::vector<long double > >* Jvec, int first_look_index, long double missing, std::vector<std::vector<long double> >* Allfits, long double investor, int num_partitions, std::string delimit, std::string input_file_name, std::string sample, int z, std::vector<std::vector<long double > >* indexes, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct, std::string sys, std::string overWriteRestore, long double baseWealth, std::string checkPoint) {
  //intializing all the objects
  long double period;
  std::vector<std::vector<long double > > new_LDL, prev_LDL;
  
  //Run period zero
  std::string restoreFile = investorResultsFileName(sys, sample, std::to_string((int) investor), std::to_string(num_partitions), input_file_name, std::to_string(z))+"-restore.txt";
  if (overWriteRestore=="F"){
    //We want to start from the last check point
    if (getRestorePoint(restoreFile, &new_LDL, &prev_LDL, LDL_num_rows, LDL_num_cols, &period, checkPoint)) {
      //We were able to start from the last check point
      period = period + 1.0;
      while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
        prev_LDL = new_LDL;
        J(&new_LDL, LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, &prev_LDL, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
        period = period + 1.0;
      }
    }
    else {
      //Error, we weren't able to start from the last check point
      //start fresh
      period = 0.0;
      prev_LDL = new_LDL;
      J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
      period = period + 1.0;
      prev_LDL = new_LDL;
      J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
      period = period + 1.0;
      while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
        prev_LDL = new_LDL;
        J(&new_LDL, LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, &prev_LDL, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
        period = period + 1.0;
      }
    }
  }
  else{
    //We don't want to start from the last check point
    //start fresh
    period = 0.0;
    prev_LDL = new_LDL;
    J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
    period = period + 1.0;
    prev_LDL = new_LDL;
    J(&new_LDL,  LDL_num_rows, LDL_num_cols, part, part->size(), disc, disc->size(), t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, A, B, G, D, T, period, Jvec, restoreFile, EUType_str, MCNum, alpha_CI, error_pct, checkPoint);
    period = period + 1.0;
    while (isEqual(&(prev_LDL[0]),&(new_LDL[0])) == false){
      prev_LDL = new_LDL;
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
  Allfits->at(6)[0] = num_partitions;
  Allfits->at(7)[0] = fits;
  std::cout << investor<< ", " << A << ", " << B << ", " << G << ", " << D << ", " << T << ", " << num_partitions << ", " << fits << std::endl;
  
  exportInvestorData(Allfits, investor, num_partitions, delimit, input_file_name, sample, z, sys);
}
