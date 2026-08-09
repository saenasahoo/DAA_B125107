import pandas as pd
import matplotlib.pyplot as plt
import os

df = pd.read_csv("results.csv")

operations = ["Search", "Insert", "Delete", "Max", "Min", "Predecessor", "Successor"]
structures = ["UnsortedArray", "SortedArray", "SLL_Unsorted", "SLL_Sorted", "DLL_Unsorted", "DLL_Sorted"]
colors = {
    "UnsortedArray": "#1f77b4",
    "SortedArray": "#ff7f0e",
    "SLL_Unsorted": "#2ca02c",
    "SLL_Sorted": "#d62728",
    "DLL_Unsorted": "#9467bd",
    "DLL_Sorted": "#8c564b",
}

os.makedirs("plots", exist_ok=True)

fig, axes = plt.subplots(4, 2, figsize=(13, 18))
axes = axes.flatten()

for idx, op in enumerate(operations):
    ax = axes[idx]
    sub = df[df.operation == op]
    for s in structures:
        d = sub[sub.structure == s].sort_values("n")
        if len(d) == 0:
            continue
        ax.plot(d.n, d.time_us, marker="o", markersize=3, label=s, color=colors[s])
    ax.set_title(op, fontsize=12, fontweight="bold")
    ax.set_xlabel("n (number of elements)")
    ax.set_ylabel("time (microseconds, log scale)")
    ax.set_yscale("log")
    ax.grid(True, which="both", alpha=0.3)

axes[-1].axis("off")
handles, labels = axes[0].get_legend_handles_labels()
fig.legend(handles, labels, loc="lower right", bbox_to_anchor=(0.98, 0.05), fontsize=11, title="Data Structure")

fig.suptitle("Dictionary ADT: Empirical Running Time vs n (per operation)", fontsize=15, fontweight="bold")
fig.tight_layout(rect=[0, 0, 1, 0.97])
fig.savefig("plots/all_operations.png", dpi=150)
print("saved plots/all_operations.png")

# Also one plot per structure, showing all its operations together
fig2, axes2 = plt.subplots(3, 2, figsize=(13, 14))
axes2 = axes2.flatten()
for idx, s in enumerate(structures):
    ax = axes2[idx]
    sub = df[df.structure == s]
    for op in operations:
        d = sub[sub.operation == op].sort_values("n")
        if len(d) == 0:
            continue
        ax.plot(d.n, d.time_us, marker="o", markersize=3, label=op)
    ax.set_title(s, fontsize=12, fontweight="bold")
    ax.set_xlabel("n")
    ax.set_ylabel("time (us, log)")
    ax.set_yscale("log")
    ax.grid(True, which="both", alpha=0.3)
    ax.legend(fontsize=8)

fig2.suptitle("Dictionary ADT: All Operations per Data Structure", fontsize=15, fontweight="bold")
fig2.tight_layout(rect=[0, 0, 1, 0.97])
fig2.savefig("plots/per_structure.png", dpi=150)
print("saved plots/per_structure.png")
