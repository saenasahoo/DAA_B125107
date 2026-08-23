# Q3 — Application of Sorting III: k Integers Summing to T
**File:** `q3_ksum.c`

## Problem
Given set `S` of `n` integers, integer `T`, and integer `k`, determine
whether some `k` elements of `S` sum to `T`, in `O(n^(k-1) · log n)`.

## Algorithm
1. Sort `S` — `O(n log n)`.
2. Recursively fix the first `(k − 2)` elements using `(k − 2)` nested
   loops over strictly increasing indices.
3. Base case (`remaining == 2`): for each candidate element in the
   remaining suffix, binary search for the complement that makes the
   partial sum equal `T`.

## Time Complexity
Let the recursion peel off one element per level until 2 remain.

| Step | Cost |
|---|---|
| Initial sort | O(n log n) |
| Choosing `k − 2` elements via nested loops (worst case, ~`n` choices per level) | O(n^(k-2)) |
| Base case: pair check via binary search, run once per combination of the outer `k-2` elements | O(n log n) |
| **Combined (dominant term)** | **O(n^(k-2) · n log n) = O(n^(k-1) log n)** |

The initial `O(n log n)` sort is dominated by `O(n^(k-1) log n)` for any
`k ≥ 2`, so the overall bound stated by the problem holds.

- **Why binary search instead of a two-pointer scan for the base case?**
  A two-pointer scan solves the pair-sum base case in `O(n)`, which would
  give a *tighter* `O(n^(k-1))` bound overall. The problem explicitly asks
  for the `log n` factor, so binary search is used deliberately for the
  base case instead of the faster two-pointer technique.

## Space Complexity
- Sorted copy of `S`: **O(n)**.
- `chosen[]` array tracking the current combination: **O(k)**.
- Recursion depth: `O(k)` stack frames (one per level of "fix an
  element"), each O(1) local state → **O(k)** auxiliary stack space.
- **Total auxiliary space: O(n + k) = O(n)** (since `k ≤ n`).
