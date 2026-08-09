"""
Plot Towers of Hanoi move counts for Question 4
(Design and Analysis of Algorithms, Lab-01).

Reads hanoi.csv (produced by hanoi.c) and produces two subplots:
  1. moves vs n on a normal axis -> shows exponential blow-up
  2. log2(moves+1) vs n -> shows a straight line (slope 1),
     confirming moves(n) = 2^n - 1 (exponential growth)

Usage:
    python3 plot_hanoi.py
Produces:
    hanoi_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("hanoi.csv")

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

ax1.plot(df["n"], df["moves"], marker="o", color="tab:red")
ax1.set_xlabel("n (number of discs)")
ax1.set_ylabel("Number of moves")
ax1.set_title("Moves vs n (linear scale)")
ax1.grid(True, linestyle="--", alpha=0.4)

ax2.plot(df["n"], df["log2_moves_plus1"], marker="o", color="tab:blue")
ax2.set_xlabel("n (number of discs)")
ax2.set_ylabel("log2(moves + 1)")
ax2.set_title("log2(moves+1) vs n -> straight line, slope 1\nconfirms moves(n) = 2^n - 1")
ax2.grid(True, linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("hanoi_plot.png", dpi=150)
print("Saved hanoi_plot.png")
