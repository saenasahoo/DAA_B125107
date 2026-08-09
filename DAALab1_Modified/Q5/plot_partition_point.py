"""
Plot partition-point search comparisons for Question 5
(Design and Analysis of Algorithms, Lab-01).

Reads partition_point.csv (produced by partition_point.c) and
plots comparisons vs n for linear scan (O(n)) and binary
search (O(log n)) on a log-x axis, side by side.

Usage:
    python3 plot_partition_point.py
Produces:
    partition_point_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("partition_point.csv")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.plot(df["n"], df["linear_comparisons"], marker="o", color="tab:red", label="Linear scan O(n)")
ax1.plot(df["n"], df["binary_comparisons"], marker="s", color="tab:blue", label="Binary search O(log n)")
ax1.set_xscale("log")
ax1.set_xlabel("n (log scale)")
ax1.set_ylabel("Comparisons")
ax1.set_title("Comparisons vs n (both methods)")
ax1.legend()
ax1.grid(True, which="both", linestyle="--", alpha=0.4)

ax2.plot(df["n"], df["binary_comparisons"], marker="s", color="tab:blue")
ax2.set_xscale("log")
ax2.set_xlabel("n (log scale)")
ax2.set_ylabel("Comparisons")
ax2.set_title("Binary search comparisons only\n(grows as log2(n))")
ax2.grid(True, which="both", linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("partition_point_plot.png", dpi=150)
print("Saved partition_point_plot.png")
