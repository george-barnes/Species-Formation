//
//  main.cpp
//  random numbers
//
//  Created by George Barnes on 08/02/2014.
//  Copyright (c) 2014 George Barnes. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <tgmath.h>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <random>
#include <iomanip>
#include <time.h>
#include <map>
using namespace std;

const int sots = 200;
int X[sots];  // contains traits of all individuals (position) and number of each (number in that position)
int X2[sots]; // second individual vector for storing new generation
double P[sots]; // contains probability of death

double prob(int i);
double rand_gauss(double pos);

double pos;
double ran_num;

const double k(1/18000.0); // remember to put .0
const double C(0.9);
const double sig(0.03);
const int time_step(300);


int main()
{

    double temp_X;
    int temp_X_int;
    
    for (int pos = 0; pos < sots; pos++) // loop over all trait positions
    {
        
        int num_of_trait = X2[pos];
        int c1 = 0;
        
        while (c1 < num_of_trait) // loop so each individual with each trait reproduces
        {
            double gauss_num = rand_gauss(pos); // generate random gaussian numbers
            
            gauss_num = (round(gauss_num*sots))/sots; // round to two decimal places
            
            if (gauss_num >= 0.0) {temp_X = (gauss_num * sots);} // conditions satisfy periodic BC's
            else {temp_X = (gauss_num * sots) + sots;}
            
            if (temp_X >= sots) {temp_X = temp_X - sots;}
            
            temp_X_int = (int) temp_X;
            
            X2[temp_X_int]++; // add offspring to new population
            
            c1++;
        }
    }
    
}

double mean;

double rand_gauss(double pos)
{
    mean = pos/sots;
    
    random_device rd;
    
    mt19937 e2(rd());
    
    normal_distribution<> dist(mean, sig);
    
    map<int, int> hist;
    
    return dist(e2);
    
}

