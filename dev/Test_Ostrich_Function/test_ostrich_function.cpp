#include "OstrichFunction.h"
#include <string>
#include <vector>
#include <iostream>

/*
Program to test the Ostrich as a full function
*/

int main(){
    long double investor = 74;
    std::string file_path= "/media/windows7/Users/Charite/Dropbox/Nachum/OstrichCPP/AWSCode/Ostrich/investorData/cluster/cluster74/88808sample74.txt";
    int max_row=504;
    long double A = 0.0;
    long double B = 0.0;
    long double G = 3.0;
    long double D = 1.0;
    long double T = 0.5;
    long double T_Max = 10.0;
    long double npart=10;
    long double MCNum = 1000;
    std::string EUType_str ="RS";
    long double alpha_CI = 0.001;
    long double error_pct = 0.001;
  
    long double fit = OstrichFunction(file_path, max_row, A, B, G, D, T, T_Max, npart, MCNum, EUType_str, alpha_CI, error_pct);
    std::cout << "Investor: " << (int) investor << std::endl;
    std::cout << "Alpha: " << A << std::endl;
    std::cout << "Beta: " << B << std::endl;
    std::cout << "Gamma: " << G << std::endl;
    std::cout << "Delta: " << D << std::endl;
    std::cout << "Theta: " << T << std::endl;
    std::cout << "T Max: " << T_Max << std::endl;
    std::cout << "Partition: " << npart << std::endl;
    std::cout << "Fit: " << fit << std::endl;
    
    return 0;
}


