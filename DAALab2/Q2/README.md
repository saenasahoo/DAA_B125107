# Merge Sort vs. Modified Merge Sort

This question compares the standard merge sort algorithm with a modified version of merge sort that divides the input array into three parts instead of two.

## Problem Statement

The modified merge sort works as follows:

1. Divide the input array into three approximately equal parts.
2. Recursively sort each of the three parts.
3. Combine the three sorted parts using a three-way merge subroutine.
4. Compare its running time with the standard merge sort.

The program experimentally validates the theoretical running times by measuring the execution time for different input sizes and plotting the order of growth.

## Algorithms

### Standard Merge Sort

Standard merge sort divides the array into two halves, recursively sorts both halves, and then merges the two sorted halves.

Its recurrence is:

```text
T(n) = 2T(n/2) + O(n)
```

Therefore, its worst-case running time is:

```text
O(n log n)
```

### Modified Three-Way Merge Sort

The modified merge sort divides the array into three parts, recursively sorts each part, and then merges the three sorted arrays.

Its recurrence is:

```text
T(n) = 3T(n/3) + O(n)
```

Therefore, its worst-case running time is:

```text
O(n log n)
```

Although both algorithms have the same asymptotic complexity, their actual running times can differ because of the different number of recursive calls and the cost of merging.

## Folder Structure

```text
Q2/
├── q2.c
├── merge_results.csv
├── merge_comparison.png
├── plot_kmerge.py
└── README.md
```

## Files Description

- `q2.c` – C program implementing standard merge sort and modified three-way merge sort.
- `merge_results.csv` – Contains the experimental running-time results.
- `merge_comparison.png` – Graph comparing the running times of the two merge sort versions.
- `plot_kmerge.py` – Python script used to generate the comparison plot.
- `README.md` – Documentation for Question 2.

## Time Complexity

| Algorithm | Division | Merge | Worst-Case Time |
|---|---|---|---|
| Standard Merge Sort | 2 parts | O(n) | O(n log n) |
| Modified Merge Sort | 3 parts | O(n) | O(n log n) |

## Objective

The objective is to determine the worst-case running time of the modified merge sort and experimentally compare its order of growth with the standard merge sort.

## Result

The program records the execution times for different input sizes in `merge_results.csv`. The results are plotted in `merge_comparison.png` to compare the growth of standard merge sort and the modified three-way merge sort.
