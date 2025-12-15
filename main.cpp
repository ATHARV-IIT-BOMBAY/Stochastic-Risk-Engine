/*
 * PROJECT: Stochastic Risk Engine
 * COMPONENT: Data Generation Engine (C++)
 * DESCRIPTION: Simulates asset price paths using Geometric Brownian Motion logic
 * with configurable Drift (Trend) and Shock (Crash) factors.
 */

#include <iostream>
#include <vector>    // For 2D Arrays (The Grid)
#include <fstream>   // For writing to "data.csv"
#include <cstdlib>   // For rand() (Random numbers)
#include <ctime>     // For time() (Seeding random numbers)
#include <cmath>     // For math functions

using namespace std;

int main() {
    // ==========================================
    // 1. CONFIGURATION
    // ==========================================
    int simulations = 100;   // Number of market scenarios to test
    int days = 30;           // Duration of simulation
    double start_price = 100.0;
    
    // Market Factors
    double drift = 0.002;    // Daily Trend (0.2% growth/day -> Bull Market)
    double shock_chance = 1; // 1% chance of a crash
    double shock_severity = -0.05; // -5% drop if crash happens

    // Seed the random number generator once at the start
    srand(time(0)); 

    // Initialize the 2D Grid
    vector<vector<double>> prices(simulations, vector<double>(days));

    // Set Day 0 prices for all simulations
    for (int i = 0; i < simulations; i++) {
        prices[i][0] = start_price;
    }

    cout << "--------------------------------------" << endl;
    cout << "   STOCHASTIC RISK ENGINE (C++)       " << endl;
    cout << "--------------------------------------" << endl;
    cout << "Initializing " << simulations << " market scenarios..." << endl;

    // ==========================================
    // 2. SIMULATION LOGIC (The Core Engine)
    // ==========================================
    for (int i = 0; i < simulations; i++) {
        for (int j = 1; j < days; j++) {
            
            // Random Fluctuation: -1.0% to +1.0%
            double fluctuation = ((rand() % 200) - 100) / 10000.0;

            // Shock Event: Sudden market crash logic
            double shock = 0.0;
            if ((rand() % 100) < shock_chance) {
                shock = shock_severity; 
            }

            // Calculate Price: Previous Price * (1 + Change)
            prices[i][j] = prices[i][j-1] * (1.0 + fluctuation + drift + shock);
        }
    }

    // ==========================================
    // 3. DATA EXPORT
    // ==========================================
    ofstream myfile;
    myfile.open("data.csv");

    for (int i = 0; i < simulations; i++) {
        for (int j = 0; j < days; j++) {
            myfile << prices[i][j] << ",";
        }
        myfile << "\n"; // New line for next simulation
    }
    myfile.close();

    cout << "Success! Generated " << (simulations * days) << " data points." << endl;
    cout << "Data saved to 'data.csv'." << endl;
    cout << "--------------------------------------" << endl;

    return 0;
}
