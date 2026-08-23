# Q5 — Application of Sorting V: Merge Overlapping Intervals
**File:** `q5_merge_intervals.c`

## Problem
Given a list `I` of `n` intervals `(x_i, y_i)`, return the merged,
non-overlapping intervals covering the same union of points, in
worst-case `O(n log n)`.

## Algorithm
1. Sort intervals by left endpoint `x_i`.
2. Sweep once: maintain a "current" merged interval; extend its right
   endpoint when the next interval overlaps or touches it, otherwise
   close it and start a new current interval.

## Time Complexity
| Step | Cost |
|---|---|
| Copy input array | O(n) |
| Sort by `x_i` (`qsort`) | O(n log n) |
| Single merge sweep | O(n) |
| **Total (worst case)** | **O(n log n)** |

## Space Complexity
- Sorted working copy `arr[]`: **O(n)**.
- Output array `out[]`: **O(n)** (at most `n` merged intervals, when
  none overlap).
- `qsort` recursion stack: O(log n) typical.
- **Total auxiliary space: O(n)**.

## Correctness check against handout example
`I = {(1,3),(2,6),(8,10),(7,18)}` sorts to
`{(1,3),(2,6),(7,18),(8,10)}` and merges to **`{(1,6),(7,18)}`**,
matching the expected output exactly.
