# Q1 — Median Without Sorting: Time & Space Complexity Analysis

## Algorithm used: Randomized Quickselect

### Time Complexity

**Partition step:** scans the sub-array once → O(high - low + 1)

**Recurrence (expected case):**
Because the pivot is chosen uniformly at random, on average it splits the
array reasonably evenly, giving the recurrence

    T(N) = T(N/2) + O(N)   (expected)

Solving with the Master Theorem (case where the work per level shrinks
geometrically, unlike merge sort's T(N/2)+T(N/2)):

    T(N) = O(N)   — expected / average case

| Case | Time Complexity | Reason |
|---|---|---|
| Best case | O(N) | Pivot always splits close to the target rank |
| **Average case** | **O(N)** | Random pivot ⇒ geometric decrease in problem size (T(N) = T(N/2) + O(N)) |
| Worst case | O(N²) | Adversarial input repeatedly picks smallest/largest element as pivot (e.g. already-sorted data with a bad deterministic pivot) — randomization makes this exponentially unlikely in practice |

For the **even-N** case we call the selection routine for two ranks
(N/2 − 1 and N/2). Each call is still O(N) expected, so the total remains
**O(N) expected**, only the constant factor roughly doubles (or stays the
same if the dual-target single-pass variant is used).

### Space Complexity

- The partitioning is done **in place** on the input array → O(1) auxiliary space.
- Recursion uses the call stack:
  - Average case recursion depth: O(log N) ⇒ O(log N) stack space
  - Worst case recursion depth: O(N) ⇒ O(N) stack space
- **Overall:** O(1) extra space (excluding recursion stack), O(log N) expected auxiliary stack space.

### Comparison with the "sort first" approach
Sorting the array (e.g. with Quick Sort / Merge Sort) and picking the
middle element costs O(N log N) time. Quickselect improves this to
**O(N) expected time**, which is why it is preferred for this problem —
we only need one (or two) order statistic(s), not a fully sorted array.

### Summary Table

| Metric | Value |
|---|---|
| Time (Average) | O(N) |
| Time (Worst) | O(N²) |
| Time (Best) | O(N) |
| Space (Auxiliary) | O(1) |
| Space (Recursion stack, avg) | O(log N) |
