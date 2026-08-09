# Performance Analysis of Bubble Sort

This question implements and compares two versions of Bubble Sort using C to analyze their efficiency based on the number of comparisons performed.

## Problem Statement

Two versions of Bubble Sort are implemented for a randomized array:

1. **Optimized Bubble Sort** – Terminates early if the array becomes sorted before completing all passes.
2. **Standard Bubble Sort** – Always completes all required passes.

The number of comparisons made by both versions is recorded and plotted for different input sizes.

## Approach

### Version 1: Early Termination

After each pass, the program checks whether any swap occurred.

- If no swap occurs, the array is already sorted.
- The algorithm terminates immediately.

This can reduce the number of comparisons for inputs that become sorted before all passes are completed.

### Version 2: Standard Bubble Sort

The standard version performs all required passes regardless of whether the array becomes sorted earlier.

## Time Complexity

| Version | Best Case | Average Case | Worst Case |
|---|---:|---:|---:|
| Early-Termination Bubble Sort | O(n) | O(n²) | O(n²) |
| Standard Bubble Sort | O(n²) | O(n²) | O(n²) |

The optimized version can perform fewer comparisons when the array becomes sorted early, while the standard version continues until all passes are completed.

## Folder Structure

```text
Q3/
├── bubble_sort.c
├── bubble_sort.csv
├── bubble_sort_plot.png
├── plot_bubble_sort.py
└── README.md
```

## Files Description

- `bubble_sort.c` – C program implementing both Bubble Sort versions and recording their number of comparisons.
- `bubble_sort.csv` – Contains the experimental comparison-count results.
- `bubble_sort_plot.png` – Plot comparing the number of comparisons made by both versions.
- `plot_bubble_sort.py` – Python script used to generate the comparison graph.
- `README.md` – Documentation for this question.

## Objective

The objective is to compare the efficiency of the two Bubble Sort implementations by analyzing the number of comparisons required for different input sizes.

## Result

The comparison counts are stored in `bubble_sort.csv`. The graph generated in `bubble_sort_plot.png` shows how the number of comparisons grows as the input size increases.

The early-termination version can save comparisons when the array becomes sorted before all passes are completed.

## Conclusion

The experiment demonstrates the benefit of adding an early-termination condition to Bubble Sort. Although both versions have O(n²) worst-case complexity, the optimized version can perform fewer comparisons when the array becomes sorted early.
