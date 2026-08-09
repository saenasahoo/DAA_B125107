# Towers of Hanoi (ToH) – Performance Analysis

## Problem Statement

Simulate the solution of the Towers of Hanoi problem for different numbers of disks `n` and analyze the total number of moves required.

The objective is to plot the number of moves against the number of disks and observe the growth of the algorithm.

## Approach

The Towers of Hanoi problem uses three rods:

- Source
- Auxiliary
- Destination

To move `n` disks:

1. Move `n-1` disks from the source rod to the auxiliary rod.
2. Move the largest disk from the source rod to the destination rod.
3. Move the `n-1` disks from the auxiliary rod to the destination rod.

The process is repeated recursively until only one disk remains.

## Time Complexity

The recurrence relation is:

`T(n) = 2T(n-1) + 1`

Therefore, the exact number of moves is:

`T(n) = 2^n - 1`

Hence, the time complexity is:

**O(2^n)**

The number of moves grows exponentially as the number of disks increases.

## Folder Structure

```text
Q4/
├── hanoi.c
├── hanoi.csv
├── hanoi_plot.png
├── plot_hanoi.py
└── README.md
```

## Files Description

- `hanoi.c` – C program that simulates the Towers of Hanoi and records the number of moves for different values of `n`.
- `hanoi.csv` – Contains the recorded number of moves.
- `hanoi_plot.png` – Graph showing the growth in the number of moves.
- `plot_hanoi.py` – Python script used to generate the graph.
- `README.md` – Documentation for the experiment.

## Result

The graph shows that the number of moves increases exponentially with the number of disks.

For `n` disks, the minimum number of moves required is:

`2^n - 1`

For example:

| Number of disks (n) | Number of moves |
|---:|---:|
| 1 | 1 |
| 2 | 3 |
| 3 | 7 |
| 4 | 15 |
| 5 | 31 |
| 6 | 63 |

## Conclusion

The experiment confirms that the Towers of Hanoi algorithm has exponential growth. The number of moves required is `2^n - 1`, giving a time complexity of **O(2^n)**. Therefore, the algorithm becomes increasingly expensive as the number of disks increases.
