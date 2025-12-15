import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.axes_grid1.inset_locator import inset_axes

# ==========================================
# 1. LOAD AND PROCESS DATA
# ==========================================
print("Reading data...")
df = pd.read_csv("data.csv", header=None)
df = df.iloc[:, :-1]  # Remove empty last column

# Transpose for plotting (Rows=Days, Cols=Simulations)
df_transposed = df.T 

# Calculate the Average Trend (The Red Line)
daily_averages = df.mean(axis=0)

# Get the final prices for Risk Analysis (Last day of every sim)
final_prices = df.iloc[:, -1]

# ==========================================
# 2. RISK ANALYSIS (MATH)
# ==========================================
# Sort the final prices from lowest (worst) to highest (best)
sorted_prices = final_prices.sort_values()

# Calculate 95% VaR (The worst 5% cutoff)
cutoff_index = int(0.05 * len(sorted_prices)) 
var_price = sorted_prices.iloc[cutoff_index]
max_loss = 100.0 - var_price

print(f"--------------------------------------")
print(f"📊 STOCHASTIC ENGINE RESULTS (100 Paths)")
print(f"Start Price:       $100.00")
print(f"Average Final:     ${daily_averages.iloc[-1]:.2f}")
print(f"--------------------------------------")
print(f"⚠️ RISK ANALYSIS (Value at Risk)")
print(f"95% Confidence:    You will likely stay above ${var_price:.2f}")
print(f"Max Potential Loss: -${max_loss:.2f} (in worst 5% of cases)")
print(f"--------------------------------------")

# ==========================================
# 3. VISUALIZATION (MAIN PLOT)
# ==========================================
print("Plotting graph...")
fig, ax = plt.subplots(figsize=(12, 7))

# Layer 1: The Cloud (All 100 Paths)
ax.plot(df_transposed, alpha=0.1, color="blue", linewidth=1)

# Layer 2: The Average Trend (Red Line)
ax.plot(daily_averages, color='red', linewidth=3, linestyle='-', label='Average Trend')

# Layer 3: The VaR Line (Green Dotted Line)
ax.axhline(y=var_price, color='green', linestyle=':', linewidth=2, label=f'95% VaR (${var_price:.2f})')

# Labels - UPDATED TITLE HERE
ax.set_title("Stochastic Risk Engine: Asset Price Projection")
ax.set_xlabel("Days")
ax.set_ylabel("Price ($)")
ax.grid(True)
ax.legend(loc='upper left')

# ==========================================
# 4. ZOOM WINDOW (INSET)
# ==========================================
# Create a smaller graph inside the main one (Bottom Right)
ax_zoom = inset_axes(ax, width="30%", height="30%", loc="lower right")

# Plot the same data on the small graph
ax_zoom.plot(df_transposed, alpha=0.15, color="blue", linewidth=1)
ax_zoom.plot(daily_averages, color='red', linewidth=2)
ax_zoom.axhline(y=var_price, color='green', linestyle=':', linewidth=2)

# Focus only on the last 5 days
ax_zoom.set_xlim(25, 29) 

# Focus Y-axis near the final prices
last_avg = daily_averages.iloc[-1]
ax_zoom.set_ylim(last_avg - 8, last_avg + 8) # Wider view to see volatility

ax_zoom.set_title("Zoom: Final Days")
ax_zoom.grid(True)

print("Done! Check the popup window.")
plt.show()
