//in makeComparable.cpp

#include "makeComparable.h"
#include <algorithm>

void makeComparable(std::vector<std::vector<long double> >* investor_data, int first_look_index, long double T, long double D, std::vector<long double>* part, int part_size, std::vector<long double>* t_max, std::vector<std::vector<long double > >* indexes, long double missing, long double baseWealth){
  /* ****************************************************************************************************************
  Program to convert portfolio returns and looks/not looks to the 4 state space variables: approximate wealth, benchmark,
  days since last look, wealth at last look. Then, it converts these state space variables to the index value of our
  Action (J) std::vector (also known as A*). Individual_data columns are 'ID' 'log1' 'log2' 'rpt' 'rmt'.
  This program assumes log-continuous  converted values, which may be false.
  **************************************************************************************************************** */
  long double part_width = (part->at(1)) - (part->at(0));
  long double actual_w = baseWealth;
  long double approx_w = baseWealth;
  long double bench = baseWealth;
  long double Tt = 1.0;
  long double W_Tt = baseWealth;
  int w_x, b_x, t_x, wT_x;
  /* *****************************************************************************
  Intended structure of Index:
  [0]  Vector of indexes meant to map element of state space to a trading day in the investor's history
  [1]  Vector of implied actual wealth values from investor's trading day statistics
  [2]  Vector of implied approx. wealth values from investor's trading day statistics
  [3]  Vector of implied benchmark values from investor's trading day statistics
  [4]  Vector of actual days since the investor last looked
  [5]  Vector of implied wealth since the investor last looked
  ***************************************************************************** */
  
  // Old RA Comment: I have left the first day unfitted because the individual MUST look
  for(int y = 1; y <= first_look_index; y++){ //all values before/up to first look set to NaN, thus they go uncompared
    (indexes->at(0))[y-1] = missing;
  }
  
  int NaNcount = 0;
  
  for(int x = (first_look_index+1); x <= (signed int) (investor_data->at(0)).size(); x++) {
    if (((investor_data->at(1)).at(x-1) == missing) or ((investor_data->at(3)).at(x-1) == missing) or ((investor_data->at(4)).at(x-1) == missing)){
      //missing values
      (indexes->at(0))[x-1] = missing;
      NaNcount = NaNcount + 1;
    }
    else{
      //non-missing values
      if((investor_data->at(1)).at((x-1)-(NaNcount+1)) == 1){ //Indexing adj, in Matlab code, adjustment made above
        //If the individual looked last period
        approx_w = actual_w*exp((investor_data->at(4)).at(x-1)); //update approx_w on actual wealth (which we looked at) and market return
        bench = D*actual_w + (1.0-D)*bench;
        Tt = 1.0; //Note: we start the day after the first look, so this "one" is always approach for the first value of "x"
        W_Tt = actual_w;
        NaNcount = 0;
      }
      else{
        //If the individual did not look last period
        bench = T*approx_w + (1.0-T)*bench;
        approx_w = approx_w*exp((investor_data->at(4)).at(x-1)); // previous approx_w times market return
        Tt = Tt + 1.0;
        // W_Tt is unchanged
        NaNcount = 0;
      }
      
      // Determining the wealth and last look partition indexes of the state space variables that are closest
      // to investor state space variables stimulated above
      w_x = round(1.0*(approx_w-(part->at(0)))/part_width)+1;
      b_x = round(1.0*(bench-(part->at(0)))/part_width)+1;
      t_x = Tt;
      wT_x = round(1.0*(W_Tt-(part->at(0)))/part_width)+1;
      
      //force indexes to fall within bounds
      w_x = std::min(std::max(w_x,1), part_size);
      b_x = std::min(std::max(b_x,1), part_size);
      t_x = std::min(std::max(t_x,1), (int) (t_max->at(0)));
      wT_x = std::min(std::max(wT_x,1), part_size);
      
      //Calculate the indexes that will map rows of the the investor data matrix to rows of the new_LDL matrix
      long double ind = (w_x-1)*part_size*(t_max->at(0))*part_size + (b_x-1)*(t_max->at(0))*part_size + (t_x-1)*part_size + wT_x;
      actual_w = actual_w*exp((investor_data->at(3)).at(x-1)); // update actual_w on portfolio return
      (indexes->at(0))[x-1] = ind;
      (indexes->at(1))[x-1] = actual_w;
      (indexes->at(2))[x-1] = approx_w;
      (indexes->at(3))[x-1] = bench;
      (indexes->at(4))[x-1] = Tt;
      (indexes->at(5))[x-1] = W_Tt;
    }
  }
  
  //Col additions
  int size0 = investor_data->size();
  int size1 = size0+(indexes->size());
  investor_data->resize(size1);
  for(int j = size0; j < size1; j++){
    investor_data->at(j) = indexes->at(j-size0);
  }
  
}