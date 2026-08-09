"""
Plot bubble sort comparison counts for Question 3
(Design and Analysis of Algorithms, Lab-01).

Reads bubble_sort.csv (produced by bubble_sort.c) and plots
average number of comparisons vs n for both variants:
  - early-terminating bubble sort
  - always-complete bubble sort

Usage:
    python3 plot_bubble_sort.py
Produces:
    bubble_sort_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("bubble_sort.csv")

fig, ax = plt.subplots(figsize=(9, 6))

ax.plot(df["n"], df["avg_comparisons_early"], marker="o", label="Early-terminating bubble sort")
ax.plot(df["n"], df["avg_comparisons_full"], marker="s", label="Always-complete bubble sort")

ax.set_xlabel("n (array size)")
ax.set_ylabel("Average number of comparisons")
ax.set_title("Bubble Sort: Comparisons vs n (random data)")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("bubble_sort_plot.png", dpi=150)
print("Saved bubble_sort_plot.png")
