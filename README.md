# Stochastic Risk Engine 📊

A high-performance Quantitative Finance tool that simulates future asset price paths using a **C++ Engine** for data generation and **Python** for risk visualization.

## 🚀 Project Overview
This project models **Geometric Brownian Motion** (a Stochastic Process) to visualize the "Cone of Uncertainty" in financial markets.
- **Engine:** Built in C++ for efficient handling of 100+ simulations.
- **Visualization:** Python (Matplotlib) pipeline to render the probability distribution.
- **Risk Analysis:** Calculates **Value at Risk (VaR)** at a 95% confidence interval.

## 🛠️ Tech Stack
- **C++:** 2D Vectors, File I/O, Random Number Generation.
- **Python:** Pandas (Dataframes), Matplotlib (Visualization).
- **Math:** Drift + Shock Logic (Random Walk).

## 📸 Output
Running the simulation generates unique price paths, a calculated "Average Trend" line, and a "95% VaR" risk threshold:
![Image](https://github.com/user-attachments/assets/3ffc11de-5d51-49ec-8164-7f3ec9a0409e)

## ⚡ How to Run
1. **Compile the Engine:**
   ```bash
   g++ main.cpp && ./a.out

This generates data.csv with simulated prices.

2. **Visualize the Data:**
   ```bash
   python3 visualizer.py

This launches the interactive graph window with Zoom & Risk Analysis.

