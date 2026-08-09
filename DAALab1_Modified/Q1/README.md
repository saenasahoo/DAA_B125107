# Put the Functions in Increasing Order of Growth

This question implements the given mathematical functions in C and compares their growth rates for sufficiently large values of `n`.

## Problem Statement

The task is to place the given functions in increasing order of growth for sufficiently large values of `n`.

The program evaluates the functions for increasing values of `n` and records their values so that their relative growth can be compared experimentally.

## Approach

1. Define each given function in C.
2. Generate sufficiently large input values of `n`.
3. Calculate the value of every function for each `n`.
4. Store the results in a CSV file.
5. Plot the functions to visualize their order of growth.
6. Compare the experimental results with the theoretical asymptotic growth rates.

## Asymptotic Growth

For sufficiently large `n`, functions can be compared using their dominant growth terms. Constant factors and lower-order terms become less significant as `n` increases.

Common growth classes, from slower to faster, include:

```text
O(log n)
O(sqrt(n))
O(n)
O(n log n)
O(n^c)       for c > 1
O(2^n)
O(3^n)
```

## Folder Structure

```text
Q1/
├── growth_functions.c
├── growth_functions.csv
├── growth_functions_plot.png
├── order_of_growth.c
├── plot_growth.py
└── README.md
```

## Files Description

- `growth_functions.c` – C program used to evaluate the given functions.
- `growth_functions.csv` – Contains the calculated values for different values of `n`.
- `growth_functions_plot.png` – Plot showing the growth of the functions.
- `order_of_growth.c` – C program used to determine and compare the order of growth.
- `plot_growth.py` – Python script used to generate the graph from the experimental results.
- `README.md` – Documentation for this question.

## Objective

The objective is to understand and experimentally verify the relative growth rates of different mathematical functions and arrange them in increasing order of growth for sufficiently large values of `n`.

## Result

The experimental values are stored in `growth_functions.csv`. The graph generated in `growth_functions_plot.png` provides a visual comparison of the growth rates.

## Conclusion

The experiment verifies the concept of asymptotic growth and shows why the dominant term of a function determines its order of growth for sufficiently large input sizes.
