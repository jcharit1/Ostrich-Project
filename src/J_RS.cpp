//in J_RS.cpp

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
  long double B_reset, term_A, term_B; //utility from looking (term_A) and utility from not looking (term_B)
  long double act_w_x, act_w_x_1; //actual wealth
  long double approx_w_minus_one_L, approx_w_minus_one_DL, bench_minus_one_L, bench_minus_one_DL, t_minus_one_L, t_minus_one_DL, approx_wT_minus_one_L, approx_wT_minus_one_DL; //future period state space variables (note last period is time ==0)
  long double conditional_prob, total_prob;
  int w_L, w_DL, b_L, b_DL, t_L, t_DL, wT_L, wT_DL, index_L, index_DL; //index variables
  long double J_0, Jvec_L, Jvec_DL; //utility value variables
  int numDraws; //number of draws
  long double delta_t = (1.0/250.0); //based on number of trading days
  long double m, v; //mean and variance of conditional lognormal actual wealth distribution
  int t_max_size = t_max->at(0);
  long double part0 = part->at(0);
  
  //Analysis for both approaches that can be pulled out of the loop
  //////////////////////////////////////////////////////////////////////////////////////
  t_minus_one_L = 1.0; //redundant but the hope pattern makes the code easier to follow
  t_L = t_minus_one_L;
  t_L = std::min(std::max(t_L,1), t_max_size);
  int x = 1; //used to index the rows of the LDL vectors, represents an element of the entire state space
  if(period == 0){ //first time calling the J() function, at the final period of the dynamic programming therefore, no look decisions
    //looping over approximate wealth
    for(int w = 1; w <= part_size; w++){
      //looping over the benchmark
      for(int b = 1; b <=part_size; b++){
        //Calculating the utility associate with each state space in the final period (note time ==0 is the final period, hence J_0)
        if(approx_w->at(w-1) >= bench->at(b-1)){
          J_0 = (1.0+A)*(approx_w->at(w-1) - bench->at(b-1));
        }
        else{
          J_0 = G*(1.0+A)*(approx_w->at(w-1) - bench->at(b-1));
        }
        //looping over time since last looked, important for the look/don't look decision, but we are at the last period so it doesn't matter
        for(int t = 1; t <=(t_max_size); t++){
          //looping over wealth since last looked, important for the look/don't look decision, but we are at the last period so it doesn't matter
          for(int wT = 1; wT <= part_size; wT++){
            if(approx_w->at(w-1) >= bench->at(b-1)){
              (new_LDL->at(0)).at(x-1) = 1.0;
              (new_LDL->at(1)).at(x-1) = J_0;
            }
            else{ //Note: If less than the benchmark, times GAMMA
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
        if(approx_w->at(w-1) >= bench->at(b-1)){
          B_reset = approx_w->at(w-1) - bench->at(b-1);
        }
        else{
          //% If less than the benchmark, times GAMMA
          B_reset = G*(approx_w->at(w-1) - bench->at(b-1));
        }
        
        //Calculating the future period benchmark if the investor doesn't look
        bench_minus_one_DL = T*(approx_w->at(w-1)) + (1.0-T)*(bench->at(b-1));
        //Determining the partition index of the nearest benchmark value to bench_minus_one_DL
        b_DL = round((bench_minus_one_DL-part0)/part_width)+1.0;
        b_DL = std::min(std::max(b_DL,1), part_size);
        
        //looping over time since last looked
        for(int t = 1; t <=(t_max_size); t++) {
          //Variance of the conditional wealth distribution
          v = delta_t*t*(1.0-pow(corr, 2.0))*pow(std_rpt,2.0);
          
          //determing the number of periods since last look for one period in the future (note: t==0 for last period so "minus_one" is one period in the future),
          //then forcing the look value to be within the bounds of 1 and the maximum number of periods that we assume the investor will wait before looking
          t_minus_one_DL = t+1.0; //don't look in this period, so add one to time since last look for next period
          t_DL = t_minus_one_DL; //L: look, DL: don't look
          t_DL = std::min(std::max(t_DL,1), t_max_size);
          //looking over actual wealth since last looked
          for(int wT = 1; wT <= part_size; wT++){
            
            // Determining the wealth since last looked for future period, if didn't look
            approx_wT_minus_one_DL = W_Tt->at(wT-1); //intentionally redundant
            wT_DL = round((approx_wT_minus_one_DL-part0)/part_width)+1.0;
            wT_DL = std::min(std::max(wT_DL,1), part_size);
            
            //After the above loop, we are done looping over the entire state space
            //again, the state space: approx wealth, benchmark, time since last looked, & wealth since last looked
            //Now, for each element of the state space, we calculate the expected utility from looking
            //and not looking, conditional and the actual wealth that could be observed and the change in next period approx. wealth as a consequence.
            term_A = 0.0; //reset/initialize term_A, term_A is the utility from looking
            term_B = B_reset; //reset term_B, term_B is the utility from not looking
            
            //Mean of the conditional wealth distribution
            m = log(W_Tt->at(wT-1))*(1-(corr*(std_rpt/std_rmt))) + log(approx_w->at(w-1))*(corr*(std_rpt/std_rmt)) + t*delta_t*(mean_rpt - (corr*(std_rpt/std_rmt))*mean_rmt); //mean
            
            //For the Riemann Sum approximations: creating the actual wealth distribution partition
            //makeActWealthPart(m, v, alpha_CI, error_pct, &act_w);
            makePart(&act_w, logNormInvCDF((alpha_CI/2.0), m, v), (int) MCNum,  logNormInvCDF(1.0-(alpha_CI/2.0), m, v)); //<-less computationally expensive but less sensitive to the distribution
            
            //Loopping over the actual wealth draws, whether through Monte Carlo distributions or looping through the partition created to Riemann sum approximations
            numDraws = act_w.size(); //the number of partitions made to the actual wealth distribution for the Riemann sum
            for(int k = 2; k <= numDraws; k++){
              //Grabbing one of the elements of the actual wealth partition
              act_w_x = act_w[(k-1)]; //use (k-1) b/c the first element of vectors is zero, but we iterate from 1 to numDraws
              act_w_x_1 = act_w[(k-2)];
              //using the lognorm pdf to get the probability of that draw
              conditional_prob = lognorm_pdf((act_w_x+act_w_x_1)/2,m,v);
              
              //%%%%%%%%%%%%%% TERM A Part 1 %%%%%%%%%%%%%%%%
              term_A = term_A + utility(((act_w_x+act_w_x_1)/2), bench->at(b-1), A, G)*conditional_prob*(act_w_x-act_w_x_1);
              
              //Next period benchmark if looks
              bench_minus_one_L = D*((act_w_x+act_w_x_1)/2) + (1.0-D)*(bench->at(b-1));
              //Determining the partition index of the nearest benchmark value to bench_minus_one_L
              b_L = 1.0*round((bench_minus_one_L-part0)/part_width)+1.0;
              b_L = std::min(std::max(b_L,1), part_size);
              
              // Determining the wealth since last looked for future period, if looked
              approx_wT_minus_one_L = (act_w_x+act_w_x_1)/2; //intentionally redundant
              wT_L = 1.0*round((approx_wT_minus_one_L-part0)/part_width)+1.0;
              wT_L = std::min(std::max(wT_L,1), part_size);
              
              //Now we loop over approx wealth values (in addition to actual wealth from the
              //loop above) and determine the expected value of the J function
              //Note: since we are using discrete values, we will do a Riemann sum approximation
              //of the expected value of the J function
              for(int j = 1; j <= disc_size; j++){ //
                approx_w_minus_one_L = (exp((disc->at(0)).at(j-1)))*((act_w_x+act_w_x_1)/2); //if looks, grow future period approx. wealth off of the actual wealth seen in current period
                approx_w_minus_one_DL = (exp((disc->at(0)).at(j-1)))*(approx_w->at(w-1)); //if doesn't look, grow future approx. wealth off of current approx. wealth
                //determining the partition index of the nearest approx. wealth to approx_w_minus_one
                w_L = 1.0*round((approx_w_minus_one_L-part0)/part_width)+1.0;
                w_L = std::min(std::max(w_L,1), part_size);
                w_DL = 1.0*round((approx_w_minus_one_DL-part0)/part_width)+1.0;
                w_DL = std::min(std::max(w_DL,1), part_size);
                
                //the x1-x4 indexes gives us the partition index of the nearest state space variables that correspond to what
                //we expect the approx. wealth, benchmark, time since last look, and wealth since last look to be in the next period
                //the index_L and index_DL variables maps the x1-x4 indexs to a row in the prev_LDL std::vector, allowing us the retrieve
                //the utility consequence of being in the state space represented by the x1-x4 indexes
                index_L = (w_L-1.0)*part_size*part_size*(t_max_size) + (b_L-1.0)*part_size*(t_max_size) + (t_L -1.0)*part_size + wT_L;
                index_DL = (w_DL-1.0)*part_size*part_size*(t_max_size) + (b_DL-1.0)*part_size*(t_max_size) + (t_DL-1.0)*part_size + wT_DL;
                
                //the conditional prob comes from the lognormal pdf function for the
                //actual wealth values drawn from our MC simulation
                total_prob = ((disc->at(1)).at(j-1))*conditional_prob;
                if(Jvec->size()== 0){
                  //Means this is the first time we ran the J() function, so the values below are just seed values
                  //the model should converge to the optimal decision regardless of the seed values
                  Jvec_L = 1.0;
                  Jvec_DL = 1.0;
                }
                else{
                  //Col. 5 is the utility consequence of being in each state space
                  //So we are using the index variables to determine the future utility consequences of looking and not looking
                  Jvec_L = ((Jvec->at(1)).at(index_L-1));
                  Jvec_DL= ((Jvec->at(1)).at(index_DL-1));
                }
                
                //%%%%%%%%%%%%%% TERM A Part 2 %%%%%%%%%%%%%%%%
                term_A = term_A + B*Jvec_L*total_prob;
                
                //%%%%%%%%%%%%%% TERM B Part 2 %%%%%%%%%%%%%%%%
                term_B = term_B + B*Jvec_DL*total_prob;
              }
            }
            //determine whether term A or B is greater and add appropriate new row to w_b_Tt_WTt_action_utility
            //I don't know why the last two columns are necessary
            if(term_A >= term_B) {
              //Utility(look) >= Utility(don't look)
              (new_LDL->at(0)).at(x-1) = 1.0;
              (new_LDL->at(1)).at(x-1) = term_A;
            }
            else{
              //Utility(look) < Utility(don't look)
              (new_LDL->at(0)).at(x-1) = 0.0;
              (new_LDL->at(1)).at(x-1) = term_B;
            }
            x = x + 1; //move to the next element of the state space and determine the look decision and associated utility consequence
          }
        }
      }
    }
  }
  //create the restore point before exiting the J() function
  createRestorePoint(restorePoint, new_LDL, Jvec, period, checkPoint);
  std::cout << "Completed period " << (int) period << ": " << ((float) (clock() - t))/CLOCKS_PER_SEC << " seconds" << std::endl;
}
