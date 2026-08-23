# Q2 — Application of Sorting II: Pair Sum from Two Sets
**File:** `q2_pair_sum_two_sets.c`

## Problem
Given sets `S1`, `S2` (each size `n`) and integer `x`, determine whether
some `a ∈ S1`, `b ∈ S2` satisfy `a + b = x`.

## Algorithm
1. Sort `S2`.
2. For every `a` in `S1`, binary search for `x - a` in sorted `S2`.

## Time Complexity
| Step | Cost |
|---|---|
| Sort `S2` (`qsort`) | O(n log n) |
| `n` binary searches, each O(log n) | O(n log n) |
| **Total** | **O(n log n)** |

## Space Complexity
- A copy of `S2` is made before sorting (to avoid mutating caller's array): **O(n)**.
- Sorting is done in place on that copy: O(log n) auxiliary stack space
  for `qsort`'s internal recursion (typical implementation), or O(1) if
  an iterative/heap sort were used.
- No other data structures scale with input.
- Overall auxiliary space: **O(n)** (dominated by the sorted copy).

## Notes
- `S1` is scanned in its original order and never copied — only `S2` is
  duplicated and sorted, since we need `S1`'s order-independent membership
  test against a *searchable* copy of `S2`.
- A hashing-based alternative (`insert all of S2` into a hash set, then
  probe with `x - a`) achieves expected **O(n)** time and **O(n)** space,
  but the problem explicitly asks for the sorting-based O(n log n) approach.
