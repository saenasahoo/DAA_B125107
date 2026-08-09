import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv("kmerge_results.csv")

labels = {"Method1_Sequential": "Method 1: Sequential merge  O(k^2 n)",
          "Method2_Pairwise": "Method 2: Pairwise/tournament merge  O(kn log k)"}
colors = {"Method1_Sequential": "#1f77b4", "Method2_Pairwise": "#d62728"}

fig, axes = plt.subplots(1, 2, figsize=(14, 5.5))

# --- Experiment A: fixed n=2000, vary k ---
ax = axes[0]
subA = df[df.n == 2000]
for m in labels:
    d = subA[subA.method == m].sort_values("k")
    ax.plot(d.k, d.time_us, marker="o", markersize=4, label=labels[m], color=colors[m])

# reference curves scaled to match at largest k
dm1 = subA[subA.method == "Method1_Sequential"].sort_values("k")
k_ref = dm1.k.values
k2n = (k_ref ** 2) * 2000
c1 = dm1.time_us.values[-1] / k2n[-1]
ax.plot(k_ref, c1 * k2n, linestyle="--", color="gray", alpha=0.7, label="c * k^2 n (reference)")

dm2 = subA[subA.method == "Method2_Pairwise"].sort_values("k")
knlogk = k_ref * 2000 * np.log2(k_ref)
c2 = dm2.time_us.values[-1] / knlogk[-1]
ax.plot(k_ref, c2 * knlogk, linestyle=":", color="black", alpha=0.7, label="c * kn log k (reference)")

ax.set_xscale("log"); ax.set_yscale("log")
ax.set_xlabel("k (number of arrays), n fixed = 2000")
ax.set_ylabel("time (microseconds, log scale)")
ax.set_title("Varying k (n = 2000 fixed)")
ax.legend(fontsize=7.5)
ax.grid(True, which="both", alpha=0.3)

# --- Experiment B: fixed k=32, vary n ---
ax = axes[1]
subB = df[df.k == 32]
for m in labels:
    d = subB[subB.method == m].sort_values("n")
    ax.plot(d.n, d.time_us, marker="o", markersize=4, label=labels[m], color=colors[m])
ax.set_xscale("log"); ax.set_yscale("log")
ax.set_xlabel("n (size of each array), k fixed = 32")
ax.set_ylabel("time (microseconds, log scale)")
ax.set_title("Varying n (k = 32 fixed)")
ax.legend(fontsize=8)
ax.grid(True, which="both", alpha=0.3)

fig.suptitle("Merging k Sorted Arrays: Sequential O(k^2 n) vs Pairwise O(kn log k)", fontsize=13, fontweight="bold")
fig.tight_layout(rect=[0, 0, 1, 0.94])
fig.savefig("kmerge_comparison.png", dpi=150)
print("saved kmerge_comparison.png")
