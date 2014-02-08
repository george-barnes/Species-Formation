//
//  main.cpp
//  trial speed improvements
//
//  Created by George Barnes on 08/02/2014.
//  Copyright (c) 2014 George Barnes. All rights reserved.
//

// Getting (what is probably slightly wrong code) to run faster
// Possibly using pointers to alter array

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

const int sots = 100;
const double power = log10(sots);

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
const int time_step(750);

double temp_P;
double temp_X;

char name[20] = "Generation";

int main()
{
    // Assign initial individual characteristics and put into array of characteristics (X)
    
    for (int j = 0; j < sots; j++)
    {
        X[j] = 75;
    }
    int z = 0;
    
    while (z < time_step)
    {
        
        cout << z << endl; // keep track of generation for timing
        
        if (z == 8 || z == 15 || z == 30 || z == 40)
        {
            int sum = 0;
            for (int j = 0; j < sots; j++) // Check if the pop = 0 to avoid wasting time
            {
                sum = sum + X[j];
            }
            if (sum == 0)
            {
                cout << "EVERYONE IS DEAD " << z << endl;
            }
        }
        
        srand(time(NULL));
        
        for (int i = 0; i < sots; i++)
        {
            P[i] = prob(i); // Assign probability of survival to array (P)
            temp_P = P[i];
            temp_X = X[i];
            
            int y = 0;
            
            while (y < temp_X) // Loop over number of individuals in each group from generation
            {
                ran_num = (rand() % (sots+1) + 0); // generate random numbers
                
                ran_num = ran_num/sots;
                
                if (temp_P < ran_num) // compare with P
                {
                    X2[i]++; // build new population from those that survive random number trial
                }
                y++;
            }
        }
        
        // Asexual gaussian reproduction of survivors of generation t
        
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
        
        for (int j = 0; j < sots; j++)  // copy population from X2 to X and wipe X2
        {
            X[j] = X2[j];
            X2[j] = 0;
        }
        
        z++; // increment generation counter
    }
    
    ofstream Emyfile(name);
    
    if (Emyfile.is_open())
    {
        
        for (int l = 0; l < sots; l++)
        {
            Emyfile << X[l] << "\n";
        }
        
        Emyfile.close();
    }
    
    return 0;
}

// Calculates the probability of survival of each individual

double prob(int i)
{
    double pi;
    double p = 0;
    double dist, temp;
    for (int j = 0; j < sots; j++)
    {
        if (j != i) // no individual competes with itself
        {
            temp = (i - j)/sots;
            
            if (abs(temp) > 0.5)
            {
                dist = 1.0 - abs(temp);
            }
            else
            {
                dist = abs(temp);
            }
            
            pi = X[j] * (k) * exp(-((dist*dist)/2*(C*C)));
            
            p=p+pi;
        }
    }
    
    return p;
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

// spare code

/*
 // print end state to file each time
 
 snprintf(name, sizeof(char) * 20, "Generation%i.txt" ,z);
 
 ofstream Emyfile(name);
 
 if (Emyfile.is_open())
 {
 
 for (int l = 0; l < sots; l++)
 {
 Emyfile << X[l] << "\n";
 }
 
 Emyfile.close();
 }
 */


