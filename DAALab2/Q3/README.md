# Merging k Sorted Arrays

This question considers the problem of merging `k` sorted arrays, each containing `n` elements, into one sorted array containing `kn` elements.

Two different methods are implemented and compared experimentally.

## Problem Statement

Given `k` sorted arrays, each having `n` elements, the goal is to combine them into a single sorted array of `kn` elements.

### Method 1: Repeated Merging

The first method merges the arrays repeatedly:

1. Merge the first two arrays.
2. Merge the resulting array with the third array.
3. Continue merging the result with the fourth array.
4. Continue until all `k` arrays have been merged.

The worst-case running time is:

```text
O(nk² log k)
```

Equivalently, since the total number of elements is `N = kn`:

```text
O(Nk log k)
```

### Method 2: Pairwise Merging

The second method divides the `k` arrays into pairs and merges each pair.

The process is repeated on the resulting arrays until only one sorted array remains.

At each level, all `kn` elements are processed, and there are `O(log k)` levels.

Therefore, the running time is:

```text
O(kn log k)
```

or, using `N = kn`:

```text
O(N log k)
```

## Comparison

| Method | Approach | Worst-Case Running Time |
|---|---|---|
| Method 1 | Repeatedly merge the accumulated result with the next array | O(nk² log k) |
| Method 2 | Pairwise merging in levels | O(nk log k) |

Method 2 is asymptotically more efficient because it keeps the total amount of work at each merging level approximately proportional to `kn`.

## Folder Structure

```text
Q3/
├── q3.c
├── kmerge_results.csv
├── kmerge_comparison.png
├── plot_kmerge.py
└── README.md
```

## Files Description

- `q3.c` – C program implementing both methods for merging `k` sorted arrays.
- `kmerge_results.csv` – Contains the experimental running-time results.
- `kmerge_comparison.png` – Graph comparing the performance of the two methods.
- `plot_kmerge.py` – Python script used to generate the comparison graph.
- `README.md` – Documentation for Question 3.

## Objective

The objective is to implement and compare two methods for merging `k` sorted arrays and experimentally validate their worst-case running times.

## Result

The program records the execution times for different values of `k` and `n` in `kmerge_results.csv`. The results are plotted in `kmerge_comparison.png` to compare the growth of both methods.

## Conclusion

Method 1 repeatedly merges an increasingly large array and therefore performs more work as the number of arrays increases.

Method 2 uses balanced pairwise merging, reducing the number of times each element participates in a merge. Hence, Method 2 has the better asymptotic running time:

```text
Method 1: O(nk² log k)
Method 2: O(nk log k)
```
