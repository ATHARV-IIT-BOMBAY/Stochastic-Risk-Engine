#include <iostream>
#include <vector>    // For 2D Arrays (The Grid)
#include <fstream>   // For writing to "data.csv"
#include <cstdlib>   // For rand() (Random numbers)
#include <ctime>     // For seeding random numbers (so they change every time)
#include <cmath>     // For math functions

using namespace std;

int main() {
    // 1. SETUP

    int simulations = 100;
    int days = 30;    
    double start_price = 100.0;

    double drift = 0.002;

    vector<vector<double>> prices(simulations, vector<double>(days));

    for (int i = 0; i < simulations; i++) {
        prices[i][0] = start_price;
    }

    cout << "Grid created!" << endl;
    cout << "Sim 0, Day 0 Price: $" << prices[0][0] << endl;

    cout << "Stock Simulator Engine is running..." << endl;

    // 2. LOGIC
    
    srand(time(0));

    for (int i = 0; i < simulations; i++){
        for (int j =1; j < days; j++){
            double fluctuation = ((rand()%200)-100)/10000.0;

            double shock = 0.0;
            if ((rand() % 100) == 0) {
                shock = -0.05;
            }
            prices[i][j] = prices[i][j-1] * (1 + fluctuation + drift + shock);
        }
    }

    cout << "Sim 0, Final Price: $" << prices[0][days-1] << endl;

    // 3. EXPORT

    ofstream myfile;
    myfile.open("data.csv");

    for (int i = 0; i < simulations; i++) {
        for (int j = 0; j < days; j++) {
            myfile << prices[i][j] << ",";
        }
        myfile << "\n";
    }
    myfile.close();

    cout << "Success! Data saved to data.csv" << endl;
    return 0;
}