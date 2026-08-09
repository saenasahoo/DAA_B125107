"""
Plot the order of growth of the 12 functions from Question 1
(Design and Analysis of Algorithms, Lab-01).

Reads growth_functions.csv (produced by order_of_growth.c) and
plots ln(value) vs n for each function, so that functions
spanning many orders of magnitude (like 3^n) can all be shown
on one readable chart.

Usage:
    python3 plot_growth.py
Produces:
    growth_functions_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("growth_functions.csv")

fig, ax = plt.subplots(figsize=(10, 7))

for func_name, group in df.groupby("function"):
    group = group.sort_values("n")
    ax.plot(group["n"], group["log_value"], marker="o", label=func_name)

ax.set_xscale("log")
ax.set_xlabel("n (log scale)")
ax.set_ylabel("ln(f(n))")
ax.set_title("Order of Growth: ln(f(n)) vs n")
ax.legend(loc="upper left", fontsize=8, ncol=2)
ax.grid(True, which="both", linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("growth_functions_plot.png", dpi=150)
print("Saved growth_functions_plot.png")
