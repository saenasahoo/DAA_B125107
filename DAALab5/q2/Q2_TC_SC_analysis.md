# Q2 — K'th Smallest Without Sorting: Time & Space Complexity Analysis

## Algorithm used: Randomized Quickselect

### Time Complexity

Each call to `partition` does O(high − low + 1) work. Unlike Quick Sort,
Quickselect recurses into only **one** side after partitioning (the side
containing rank k), never both.

**Recurrence (expected case):**

    T(N) = T(N/2) + O(N)     (random pivot ⇒ expected geometric shrinkage)

which solves to:

    T(N) = O(N)

| Case | Time Complexity | Reason |
|---|---|---|
| Best case | O(N) | Pivot lands near/at rank k quickly |
| **Average case** | **O(N)** | Randomized pivot ⇒ each recursive call operates on a constant fraction of the previous size, geometric series sums to O(N) |
| Worst case | O(N²) | Every partition is maximally unbalanced (e.g. pivot always smallest/largest element) — extremely unlikely with random pivot selection |

This is asymptotically **better than sorting** (O(N log N)) because we
discard the irrelevant half of the array at every step instead of fully
ordering it.

### Space Complexity

- In-place partitioning ⇒ **O(1)** auxiliary space for the array itself.
- Recursion stack:
  - Average case: O(log N) (problem size shrinks geometrically)
  - Worst case: O(N) (linear recursion chain in the adversarial case)
- **Overall:** O(1) extra space, O(log N) expected recursion depth.

### Summary Table

| Metric | Value |
|---|---|
| Time (Average) | O(N) |
| Time (Worst) | O(N²) |
| Time (Best) | O(N) |
| Space (Auxiliary) | O(1) |
| Space (Recursion stack, avg) | O(log N) |

### Note on deterministic O(N) worst case
A guaranteed worst-case O(N) is possible using the **Median-of-Medians**
pivot selection strategy (Blum–Floyd–Pratt–Rivest–Tarjan, 1973), at the
cost of a larger constant factor. This lab uses the simpler randomized
version, which is faster in practice for typical/uniformly random input.
