# Find the Partition Point

## Problem Statement

Given an array `A` with `n` elements containing a run of `0`s followed by a run of `1`s, find the exact point where the transition between `0` and `1` occurs.

The objective is to implement the method in C and analyze its performance for different input sizes.

## Approach

The array has the following form:

```text
0 0 0 0 0 1 1 1 1 1
              ^
       partition point
```

The program finds the first occurrence of `1`, which represents the partition point between the two runs.

A binary-search based approach can be used because the array is sorted in the form of all `0`s followed by all `1`s.

### Binary Search

1. Set `low = 0` and `high = n - 1`.
2. Find the middle position.
3. If `A[mid]` is `1`, continue searching on the left side.
4. If `A[mid]` is `0`, continue searching on the right side.
5. The first position containing `1` is the required partition point.

## Time Complexity

The binary search reduces the search range by half at every step.

- **Best Case:** O(1)
- **Average Case:** O(log n)
- **Worst Case:** O(log n)
- **Space Complexity:** O(1)

## Folder Structure

```text
Q5/
├── partition_point.c
├── partition_point.csv
├── partition_point_plot.png
├── plot_partition_point.py
└── README.md
```

## Files Description

- `partition_point.c` – C program used to find the partition point.
- `partition_point.csv` – Contains the experimental results for different input sizes.
- `partition_point_plot.png` – Plot showing the growth of the running time/operations.
- `plot_partition_point.py` – Python script used to generate the graph.
- `README.md` – Documentation for this question.

## Result

The program correctly identifies the first `1` in an array consisting of a sequence of `0`s followed by a sequence of `1`s.

The experimental plot demonstrates the logarithmic growth expected from the binary-search approach.

## Conclusion

The partition point can be found efficiently using binary search. Since the search space is divided into half at each step, the worst-case running time is **O(log n)**, making the method efficient for large input sizes.
