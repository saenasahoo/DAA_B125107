"""
Plot element-uniqueness comparison counts for Question 6
(Design and Analysis of Algorithms, Lab-01).

Reads uniqueness.csv (produced by uniqueness.c) and plots
comparisons vs n for the naive O(n^2) method and the
sort-then-scan O(n log n) method, on both linear and log-log
axes.

Usage:
    python3 plot_uniqueness.py
Produces:
    uniqueness_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("uniqueness.csv")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.plot(df["n"], df["naive_comparisons"], marker="o", color="tab:red", label="Naive O(n^2)")
ax1.plot(df["n"], df["sorted_comparisons"], marker="s", color="tab:blue", label="Sort-then-scan O(n log n)")
ax1.set_xlabel("n")
ax1.set_ylabel("Comparisons")
ax1.set_title("Comparisons vs n (linear scale)")
ax1.legend()
ax1.grid(True, linestyle="--", alpha=0.4)

ax2.plot(df["n"], df["naive_comparisons"], marker="o", color="tab:red", label="Naive O(n^2)")
ax2.plot(df["n"], df["sorted_comparisons"], marker="s", color="tab:blue", label="Sort-then-scan O(n log n)")
ax2.set_xscale("log")
ax2.set_yscale("log")
ax2.set_xlabel("n (log scale)")
ax2.set_ylabel("Comparisons (log scale)")
ax2.set_title("Comparisons vs n (log-log scale)")
ax2.legend()
ax2.grid(True, which="both", linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("uniqueness_plot.png", dpi=150)
print("Saved uniqueness_plot.png")
