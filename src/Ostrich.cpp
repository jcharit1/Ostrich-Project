#include "investor_data.h"
#include "vec_functions.h"
#include "vec_stat.h"
#include "part_functions.h"
#include "NDiscrete.h"
#include "investorThread.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

/*
Program one of the Ostrich project
    using only the dynamic Reimann sum approach for partitioning the actual wealth distribution

*/

int main(int argc, char *argv[]){
    //Parameters necessary for pulling the data
	  std::string file_path = argv[1]; //path of the data
	  std::string sample = argv[2]; //sample
    std::string mrow = argv[3]; //# of rows in the data
    std::string input_file_name = argv[4]; //name associated with the parameter space

    //Parameter Inputs
    std::string alpha = argv[5]; //utility parameter
    std::string beta = argv[6]; //utility parameter
    std::string gamma = argv[7]; //utility parameter
    std::string delta = argv[8]; //utility parameter
    std::string theta = argv[9]; //utility parameter
    std::string t_max_str = argv[10]; //utility parameter
    std::string npart_str = argv[11]; //partition for the state space variables: [approx wealth X benchmark X time since last looked X wealth since last looked]
    std::string z_str = argv[12]; //index for the element of each investor's parameter space used to run the model

    //Inputs for the Monte Carlo Simulations or Riemann approximation
    std::string EUType_str = argv[13]; //method for estimating the expected utility -- MC: Monte Carlo, RS: Riemann Sum
    std::string MCNum_str = argv[14]; //# of draws for Monte Carlo simulation
    std::string alpha_CI_str = argv[15]; //1-alpha_CI is the percent of mass under the actual wealth distribution that we would like to attempt to estimate with Riemann sum
    std::string error_pct_str = argv[16]; //the error tolerance for the Riemann sum approximation

    //System Information
    std::string sys = argv[17]; //flag for the computer used to run the model

    //Dealing with restore files
    std::string checkPoint = argv[18]; //T or F, make restore files?
    std::string overWriteRestore = argv[19]; //T or F, ignore restore points and start from scratch?

    //Converting the data parameters
    int max_row = atoi(mrow.c_str());

    //Translating the Parameter Inputs to long double strtold(id.c_str(), NULL);
    long double A = strtold(alpha.c_str(), NULL);
    long double B = strtold(beta.c_str(), NULL);
    long double G = strtold(gamma.c_str(), NULL);
    long double D = strtold(delta.c_str(), NULL);
    long double T = strtold(theta.c_str(), NULL);
    std::vector<long double> t_max = {strtold(t_max_str.c_str(), NULL)}; //leaving it as a std::vector for future flexibility
    long double npart = strtold(npart_str.c_str(), NULL);
    long double MCNum = strtold(MCNum_str.c_str(), NULL);
    long double alpha_CI = strtold(alpha_CI_str.c_str(), NULL);
    long double error_pct = strtold(error_pct_str.c_str(), NULL);
    int z = stoi(z_str); //indexes the elements of the parameter space

    //Stepping out other helper variables
    std::string delimit = ", "; //delimiter for output
    //Points to keep track of data
    long double missing = -999.0; //the missing values are stored as -999 in the text file
    std::vector<long double> LDbufvec;

    int num_partitions = (int) npart; //Defines the number of wealth partitions created
    std::vector<std::vector<long double > > Jvec; // passed through J function
    int num_para = 5; //number of utility parameters

    //Import of investor data file
    //Data formatted as columns: "ID", "log", "rpf", "rmkt"
    std::vector<long double> ID(max_row, 0);
    std::vector<long double> LOG(max_row, 0);
    std::vector<long double> RPF(max_row, 0);
    std::vector<long double> RMKT(max_row, 0);
    std::vector<std::vector<long double>* > all_data = {&ID, &LOG, &RPF, &RMKT};
    importInvestorData(max_row, file_path, &all_data);

    //End if the data set is empty
    if((all_data[0]->at(0) == 0) & (all_data[1]->at(0)  == 0) & (all_data[2]->at(0)  == 0) & (all_data[3]->at(0)  == 0)){
        std::cout << "Empty dataset!" << std::endl;
        return 0;
    }
    //Getting investor IDs, the first column of data and generating investor level data
    std::vector<long double> investor_ids = *(all_data[0]); //getting the data
    sort(investor_ids.begin(),investor_ids.end()); //sort the data b/c unique() only removes consecutive duplicates
    std::vector<long double>::iterator it = unique(investor_ids.begin(),investor_ids.end()); //removing consecutive duplicates
    investor_ids.resize(distance(investor_ids.begin(),it)); //resizing the std::vector b/c unique() doesn't change the size
    std::vector<long double> investor_ID;
    std::vector<long double> investor_LOG;
    std::vector<long double> investor_RPF;
    std::vector<long double> investor_RMKT;
    std::vector<std::vector<long double> > investor_data;
    investor_data.push_back(investor_ID);
    investor_data.push_back(investor_LOG);
    investor_data.push_back(investor_RPF);
    investor_data.push_back(investor_RMKT);
    std::vector<std::vector<std::vector<long double> > > investor_all(investor_ids.size(), investor_data);
    getInvestorData(&all_data, &investor_ids, &investor_data, &investor_all);

    //deleting the original dataset to free memory (swaping vectors with empty vectors deletes them)
    for(int i = 0; i<  (signed int) all_data.size(); i++){
        //Looping through all the pointers to std::vector<long double>s, dereferencing them and deleting them
        std::vector<long double>().swap(*(all_data[i]));
        //delete all_data[i]; //all_data[i] is a pointer
    }
    std::vector<std::vector<long double>* >().swap(all_data);

    //I general, we will not actually looping over multiple investors, just one.
    //This is low (computational) cost structure from an old version of the code
    //that allows us to iterate through multiple investors if we ever wanted to

    for(int i = 0; i< (signed int) investor_ids.size(); i++){
        long double investor = investor_ids[i];
        int cl_int = (((int) investor) % 500); //needed for the file structure, investor input and output files are map into 500 folders by investor ID
        std::string cl = std::to_string(cl_int);
        int first_look_index = findInLDVector(&(investor_all[i][1]), 1.0); // Note on "investor_all[i][1]" i refers to the ith investor dataset, 1 is the look/notlook col of that dataset
        int days = (investor_all[i][1]).size() - first_look_index - countInLDVec(&(investor_all[i][1]), missing) + 1; //Number of days left
        if (days == 0){
            std::cout << "There are just " << days << " days left! Exiting program." << std::endl;
            return 0;
        }

        //Create investor data without missing values
        //Clearing variables
        std::vector<std::vector<long double> > investordata_NaNfree(investor_all[0].size(),LDbufvec);
        std::vector<long double> cont_rpt;
        std::vector<long double> cont_rmt;
        /* *****************************************************************************
            Structure of Investordata_NaNfree at this point in the code:
                [0] std::vector of investor IDs
                [1] std::vector of look and don't look decisions
                [2] std::vector of personal returns
                [3] std::vector of market returns
        ***************************************************************************** */

        //The second to last argument of replaceMissing() is a flag for either replacing the
        //missing values (==1) or removing the missing values (==0) and associated observations.
        //The last argument is the value used to replace the missing values
        replaceMissing(&investordata_NaNfree, &investor_all, missing, i, 0, 0);

        //Stopping if investors never look or always look
        int look_sum = sumVec(&(investordata_NaNfree[1]));
        if ((look_sum == 0) | (look_sum == (signed int) (investordata_NaNfree[1]).size())){
            std::cout << "Error: investor never looked or always looked!" << std::endl;
            return 0;
        }

        //Creating continuos return time series
        cont_rpt.resize(investordata_NaNfree[2].size());
        cont_rmt.resize(investordata_NaNfree[3].size());
        for(int k = 0; k < (signed int) cont_rpt.size(); k++){
            cont_rpt[k] = log(investordata_NaNfree[2][k]);
            cont_rmt[k] = log(investordata_NaNfree[3][k]);
        }

        //Descriptive statistics
        long double mean_rpt = meanVec(&cont_rpt);
        long double std_rpt = sqrt(varVec(&cont_rpt, 1.0)); //the one menas I want 1.0/(n-1.0)
        long double mean_rmt = meanVec(&cont_rmt);
        long double std_rmt = sqrt(varVec(&cont_rmt, 1.0)); //the one menas I want 1.0/(n-1.0)

        //Normalized wealth series
        long double baseWealth = 100.0;
        std::vector<long double> pwealth = investordata_NaNfree[2]; //personal wealth
        std::vector<long double> mwealth = investordata_NaNfree[3]; //"market" wealth

        //Growing the base wealth by the first period return
        pwealth[0]= baseWealth*pwealth[0]; //personal wealth in first period
        mwealth[0]= baseWealth*mwealth[0]; //market ...

        //Growing first period wealth by rest of the returns
        for(int k = 1; k < (signed int) pwealth.size(); k++){
            pwealth[k] = investordata_NaNfree[2][k]*pwealth[k-1];
        }
        for( int k = 1; k < (signed int) mwealth.size(); k++){
            mwealth[k] = investordata_NaNfree[3][k]*mwealth[k-1];
        }

        //Bounds of the normalized wealth series
        long double p_wl = *min_element(pwealth.begin(), pwealth.end());
        long double m_wl = *min_element(mwealth.begin(), mwealth.end());
        long double p_wu = *max_element(pwealth.begin(), pwealth.end());
        long double m_wu = *max_element(mwealth.begin(), mwealth.end());

        //Destroy unneeded vectors
        std::vector<long double>().swap(pwealth);
        std::vector<long double>().swap(mwealth);

        //Now, the overall bouds are defined by the std::max and std::min bounds
        //from the set of the four bounds calculated above
        long double abs_wl = std::min(p_wl, m_wl);
        long double abs_wu = std::max(p_wu, m_wu);
        if (abs_wu == abs_wl){
            std::cout << "The partition bounds are equal to each other. Exiting the program!" << std::endl;
            return 0;
        }

        //Next, partition the interval [abs_wl, abs_wu] by N
        std::vector<long double> part; //wealth partitions
        makePart(&part,abs_wl, num_partitions, abs_wu);

        int part_size = part.size();
        // Finally, define a discrete approximation of normal return dist
        std::vector<std::vector<long double> > disc; //disc approx of normal return
        NDiscrete(&disc, mean_rpt, std_rpt, part_size); //the disc[1,9] differs from Matlab more significantly (percentage) b/c the value is small
        //note disc is part_size+1 long
        //int disc_size = disc[0].size();

        // The daily return correlation and beta P
        std::vector<std::vector<long double> > cov_matrix(2, LDbufvec);
        covMat(&cov_matrix, &cont_rpt, &cont_rmt, 1.0);
        long double corr = (cov_matrix[0][1])/(std_rpt*std_rmt);
        long double betap = (cov_matrix[0][1])/(std_rmt*std_rmt);

        // Change return columns of investor_data to continuous returns in
        // preparation for "makeComparable" function later on.
        // May seem redundant but different from continuous return time series
        // created on lines 58/59.
        (investordata_NaNfree[3]).clear();
        investordata_NaNfree[3] = cont_rpt; //portfolio return
        investordata_NaNfree.push_back(LDbufvec);
        investordata_NaNfree[4] = cont_rmt; //market return
        //Destroy unneeded vectors
        std::vector<long double>().swap(cont_rpt);
        std::vector<long double>().swap(cont_rmt);
        /* *****************************************************************************
            Structure of Investordata_NaNfree at this point in the code:
                [0] std::vector of investor IDs
                [1] std::vector of look and don't look decisions
                [2] std::vector of personal returns
                [3] std::vector of continuous personal returns
                [4] std::vector of continuous market returns
        ***************************************************************************** */

        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        %%%%%%%%%%%%%%% Now, we construct A Star and Commence Fitting %%%%%%%%%%%%%%%%%
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
        //Preallocate memory for all_fits std::vector for speed
        //six is the number of parameters
        std::vector<long double> allfitsvec(1,0);
        std::vector<std::vector<long double> > allfits(num_para+3, allfitsvec); //plus the fit
        std::vector<long double>().swap(allfitsvec); //destroy allfitsvec

        //Dims of the LDL vectors
        long double LDL_num_rows = part_size*part_size*(t_max[0])*part_size;
        long double LDL_num_cols = 2; //look decision and utility

        //Creating the indexes std::vector
        int indexes_rows = (investordata_NaNfree[0]).size();
        int indexes_cols = 6;
        std::vector<std::vector<long double > > indexes;
        indexes.resize(indexes_cols);
        for(int i=0; i<indexes_cols; i++){
            indexes[i].resize(indexes_rows);
        }

        //launching investor threads
        investorThread(A, B, G, D, T, &investordata_NaNfree, LDL_num_rows, LDL_num_cols, &part, &disc, &t_max, corr, betap, mean_rmt, mean_rpt, std_rmt, std_rpt, &Jvec, first_look_index, missing, &allfits, investor, num_partitions, delimit, input_file_name, sample, z, &indexes, EUType_str, MCNum, alpha_CI, error_pct, sys, overWriteRestore, baseWealth, checkPoint);
    }
    return 0;
}


