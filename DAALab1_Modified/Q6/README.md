# Element Uniqueness

## Problem Statement

Given `n` random numbers, implement a method in C to check whether there are any duplicate elements.

The experiment also analyzes the performance of the method for sufficiently large values of `n`.

## Approach

The program generates or takes `n` random numbers and checks whether any two elements are equal.

A straightforward approach compares each element with the elements that follow it.

For each index `i`, the program checks:

- `A[i]` against `A[i+1]`
- `A[i]` against `A[i+2]`
- and so on.

If two equal elements are found, a duplicate exists.

## Algorithm

1. Read/generate an array containing `n` random numbers.
2. Set a flag indicating that the elements are unique.
3. Compare every pair of elements.
4. If `A[i] == A[j]`, a duplicate is found.
5. Stop the search or record the result.
6. Repeat the experiment for different values of `n`.
7. Store the results and plot the performance.

## Time Complexity

For the pairwise comparison approach:

- **Best Case:** O(1) when a duplicate is found immediately.
- **Average Case:** O(n²)
- **Worst Case:** O(n²)

The worst case occurs when all elements are unique, because every pair must be checked.

**Space Complexity:** O(n) for storing the input array.

## Folder Structure

```text
Q6/
├── uniqueness.c
├── uniqueness.csv
├── uniqueness_plot.png
├── plot_uniqueness.py
└── README.md
```

## Files Description

- `uniqueness.c` – C program that checks whether duplicate elements are present.
- `uniqueness.csv` – Contains the experimental results for different input sizes.
- `uniqueness_plot.png` – Plot showing the performance of the uniqueness-checking method.
- `plot_uniqueness.py` – Python script used to generate the graph.
- `README.md` – Documentation for this question.

## Result

The experimental results show that the number of comparisons increases approximately quadratically as the input size increases.

This agrees with the theoretical worst-case time complexity of **O(n²)**.

## Conclusion

The pairwise comparison method correctly determines whether an array contains duplicate elements. However, its worst-case running time is **O(n²)**, so the number of operations grows rapidly for large input sizes.
