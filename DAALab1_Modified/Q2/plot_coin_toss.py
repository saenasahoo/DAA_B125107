"""
Plot fair vs biased coin-toss convergence for Question 2
(Design and Analysis of Algorithms, Lab-01).

Reads coin_toss.csv (produced by coin_toss.c) and plots the
estimated P(HEAD) vs number of tosses N (log scale) for both
the fair and biased coin, with reference lines at the true
probabilities.

Usage:
    python3 plot_coin_toss.py
Produces:
    coin_toss_plot.png
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("coin_toss.csv")

fig, ax = plt.subplots(figsize=(9, 6))

ax.plot(df["n"], df["fair_prob"], marker="o", label="Fair coin (estimated)")
ax.plot(df["n"], df["biased_prob"], marker="s", label="Biased coin (estimated)")

ax.axhline(0.5, color="tab:blue", linestyle="--", alpha=0.5, label="True fair p = 0.5")
ax.axhline(0.7, color="tab:orange", linestyle="--", alpha=0.5, label="True biased p = 0.7")

ax.set_xscale("log")
ax.set_xlabel("Number of tosses N (log scale)")
ax.set_ylabel("Estimated P(HEAD)")
ax.set_title("Fair vs Biased Coin: Convergence of P(HEAD) as N grows")
ax.legend()
ax.grid(True, which="both", linestyle="--", alpha=0.4)

fig.tight_layout()
fig.savefig("coin_toss_plot.png", dpi=150)
print("Saved coin_toss_plot.png")
