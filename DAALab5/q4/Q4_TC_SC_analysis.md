# Q4 — Heap Sort (File-Based): Time & Space Complexity Analysis

## Algorithm used: Heap Sort (binary max-heap, array representation)

### Time Complexity

**1. MAX_HEAPIFY(A, n, i)**
Sifts an element down a tree of height O(log n).

    T(n) = O(log n)   per call

**2. BUILD_MAX_HEAP(A, n)**
Calls MAX_HEAPIFY on n/2 nodes. Although a naive bound gives
O(n log n), a tighter analysis (summing heapify cost over each level,
which shrinks geometrically as height decreases) gives:

    BUILD_MAX_HEAP(A, n) = O(n)     (tight bound, not n log n)

**3. HEAP_SORT main loop**
Runs n − 1 times; each iteration does one swap (O(1)) and one
MAX_HEAPIFY call (O(log n)):

    Sorting loop = (n - 1) * O(log n) = O(n log n)

**Total:**

    T(n) = BUILD_MAX_HEAP + Sorting loop
         = O(n) + O(n log n)
         = O(n log n)

Crucially, Heap Sort has **the same time complexity in the best,
average, AND worst case** — there is no data-dependent degeneration
like Quick Sort's O(N²) worst case, because the heap always has
height ⌊log₂ n⌋ regardless of input order.

| Case | Time Complexity |
|---|---|
| Best case | O(N log N) |
| Average case | O(N log N) |
| **Worst case** | **O(N log N)** — guaranteed, unlike Quick Sort |

Additional linear-time costs (not affecting the dominant term):
- File generation: O(N)
- File read: O(N)
- File write: O(N)

### Space Complexity

- Heap Sort operates **in place** on the array (the "heap" is just a
  reinterpretation of the same array) → O(1) auxiliary space for data.
- MAX_HEAPIFY here is written **recursively**, giving O(log N) recursion
  stack depth (can be rewritten iteratively for true O(1) space).
- The array itself: O(N) to hold the input.

**Overall:** O(N) space for the data array, O(log N) additional
recursion-stack space (O(1) if MAX_HEAPIFY is implemented iteratively).

### Summary Table

| Metric | Value |
|---|---|
| Time (Best) | O(N log N) |
| Time (Average) | O(N log N) |
| Time (Worst) | O(N log N) — guaranteed |
| Space (Array) | O(N) |
| Space (Recursion stack) | O(log N) |

### Heap Sort vs Quick Sort (this lab's Q3)
Heap Sort trades Quick Sort's better average-case constant factor for a
**guaranteed** O(N log N) worst case and O(1) extra space (excluding the
recursion stack) — it never degrades to O(N²), making it a safer choice
when worst-case guarantees matter more than raw average speed.
