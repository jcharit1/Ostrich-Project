//in J_B0.cpp
//the when beta==0, there is a closed form expression of the expected utility

#include "J.h"
#include "part_functions.h"
#include "distribution.h"
#include "restore_point.h"
#include "utility.h"
#include <algorithm>
#include <time.h>
#include <iostream>

void J(std::vector<std::vector<long double> >* new_LDL, long double LDL_num_rows, long double LDL_num_cols, std::vector<long double>* part, int part_size, std::vector<std::vector<long double> >* disc, int disc_size, std::vector<long double >* t_max, long double corr, long double betap, long double mean_rmt, long double mean_rpt, long double std_rmt, long double std_rpt, long double A, long double B, long double G, long double D, long double T, long double period, std::vector<std::vector<long double> >* Jvec, std::string restorePoint, std::string EUType_str, long double MCNum, long double alpha_CI, long double error_pct, std::string checkPoint){
  clock_t t = clock();
  /* ***************************************************************************************************************************************
  !Important Note!
  The rows of the LDL matrix represents size of the state space. Columns 0:3 of the LDL matrix are the state space variables. Column 4 is the
  look decision, Column 5 is the expected utility associated with that decision. I don't know what the last two columns are for, the last
  programmer didn't include detailed comments. In sum, the LDL matrix records the look decision and utility consequence of the decision for all
  possible elements in the state space. The state space is the cross product of the approx. wealth, benchmark, actual wealth since last looked,
  and the max number of periods that the investor will spend without look at his/her wealth (t). We call the J() function over and over again
  until the look decision column ceases to change.
  *************************************************************************************************************************************** */
  //If the new_LDL matrix is blank
  
  if(new_LDL->size() == 0){
    new_LDL->resize(LDL_num_cols);
    for(int i = 0; i < LDL_num_cols; i++){
      new_LDL->at(i).resize(LDL_num_rows);
    }
  }
  
  //Three of the four state space variables
  ///////////////////////////////////////////////////////////////////////////////
  std::vector<long double>* approx_w = part; // approximate wealth, renamed to make coding easier
  std::vector<long double>* bench = part; // benchmark, renamed to make coding easier
  std::vector<long double>* W_Tt = part; // actual wealth at last look, renamed to make coding easier
  
  //Variables for Riemann Sum approximation
  ///////////////////////////////////////////////////////////////////////////////
  std::vector<long double> act_w; //container for the actual wealth distribution partition
  
  //Variables shared by the Monte Carlo simulations and Riemann Sum approximations
  ///////////////////////////////////////////////////////////////////////////////
  long double part_width = (part->at(1)) - (part->at(0));
  long double u_dont_look_reset, u_look, u_dont_look; //utility from looking (u_look) and utility from not looking (u_dont_look)
  long double conditional_prob, total_prob;
  long double J_0, Jvec_L, Jvec_DL; //utility value variables
  int numDraws; //number of draws
  long double delta_t = (1.0/250.0); //based on number of trading days
  long double m, v, s; //mean, variance, and std dev of conditional lognormal actual wealth distribution
  long double EW, PEW, Fb; //helper functions for calculating the expected utility
  int t_max_size = t_max->at(0);
  long double part0 = part->at(0);
  
  int x = 1; //used to index the rows of the LDL vectors, represents an element of the entire state space
  if(period == 0){ //first time calling the J() function, at the final period of the dynamic programming therefore, no look decisions
    //looping over approximate wealth
    for(int w = 1; w <= part_size; w++){
      //looping over the benchmark
      for(int b = 1; b <=part_size; b++){
        //Calculating the utility associate with each state space in the final period (note time ==0 is the final period, hence J_0)
        J_0 = utility_look(approx_w->at(w-1), bench->at(b-1), A, G);
        //looping over time since last looked, important for the look/don't look decision, but we are at the last period so it doesn't matter
        for(int t = 1; t <=(t_max_size); t++){
          //looping over wealth since last looked, important for the look/don't look decision, but we are at the last period so it doesn't matter
          for(int wT = 1; wT <= part_size; wT++){
            if(approx_w->at(w-1) >= bench->at(b-1)){
              (new_LDL->at(0)).at(x-1) = 1.0;
              (new_LDL->at(1)).at(x-1) = J_0;
            }
            else{ 
              (new_LDL->at(0)).at(x-1) = 0.0;
              (new_LDL->at(1)).at(x-1) = J_0;
            }
            x = x + 1.0;
          }
        }
      }
    }
  }
  else{ //entering this statement means we are not in the last period of the model (it is solved backward)
    //looping over approximate wealth
    for(int w = 1; w <= part_size; w++){
      //looping over benchmarks
      for(int b = 1; b <= part_size; b++){
        //Calculating utility from not looking
        u_dont_look_reset = utility_dont_look(approx_w->at(w-1), bench->at(b-1), G);
        
        //looping over time since last looked
        for(int t = 1; t <=(t_max_size); t++) {
          //Variance of the conditional wealth distribution
          v = delta_t*t*(1.0-pow(corr, 2.0))*pow(std_rpt,2.0);
          s = sqrt(v);
          
          //looking over actual wealth since last looked
          for(int wT = 1; wT <= part_size; wT++){
            //Mean of the conditional wealth distribution
            m = log(W_Tt->at(wT-1))*(1-(corr*(std_rpt/std_rmt))) + log(approx_w->at(w-1))*(corr*(std_rpt/std_rmt)) + t*delta_t*(mean_rpt - (corr*(std_rpt/std_rmt))*mean_rmt); //mean
            
            //After the above loop, we are done looping over the entire state space
            //again, the state space: approx wealth, benchmark, time since last looked, & wealth since last looked
            //Now, for each element of the state space, we calculate the expected utility from looking
            //and not looking, conditional and the actual wealth that could be observed and the change in next period approx. wealth as a consequence.
            EW = exp(m +(v/2));
            PEW = EW*0.5*(1.0+erf((m+v-log(bench->at(b-1)))/(s*sqrt(2))));
            Fb = logNormCDF(bench->at(b-1),m,v);
            u_look = (1+A)*(G*EW + (1-G)*(PEW + (bench->at(b-1))*Fb) - bench->at(b-1));
            u_dont_look = u_dont_look_reset; //reset u_dont_look, u_dont_look is the utility from not looking
            
            //determine whether term A or B is greater and add appropriate new row to w_b_Tt_WTt_action_utility
            //I don't know why the last two columns are necessary
            if(u_look >= u_dont_look) {
              //Utility(look) >= Utility(don't look)
              (new_LDL->at(0)).at(x-1) = 1.0;
              (new_LDL->at(1)).at(x-1) = u_look;
            }
            else{
              //Utility(look) < Utility(don't look)
              (new_LDL->at(0)).at(x-1) = 0.0;
              (new_LDL->at(1)).at(x-1) = u_dont_look;
            }
            x = x + 1; //move to the next element of the state space and determine the look decision and associated utility consequence
          }
        }
      }
    }
  }
  //create the restore point before exiting the J() function
  createRestorePoint(restorePoint, new_LDL, Jvec, period, checkPoint);
}
