# Q6 — Application of Sorting VI: Point Covered by Max Intervals
**File:** `q6_max_point_coverage.c`

## Problem
Given `n` intervals `[l_i, r_i]` on a line (endpoints inclusive), find a
point `p` lying in the largest number of intervals, in `O(n log n)`.

## Algorithm — Sweep Line with Tie-Breaking
1. Build `2n` events: `(l_i, START)` and `(r_i, END)`.
2. Sort events by coordinate; on ties, all `START` events are processed
   before `END` events (so a shared endpoint counts as being inside both
   intervals, since endpoints are inclusive).
3. Sweep: `START` increments the running count and is checked against the
   best-seen maximum; `END` decrements it.

## Time Complexity
| Step | Cost |
|---|---|
| Build `2n` events | O(n) |
| Sort `2n` events (comparator: coordinate, then type) | O(n log n) |
| Single sweep over `2n` events | O(n) |
| **Total** | **O(n log n)** |

## Space Complexity
- Events array of size `2n`: **O(n)**.
- `qsort` recursion stack: O(log n) typical.
- **Total auxiliary space: O(n)**.

## Why START-before-END tie-breaking matters
Because endpoints are inclusive, a point exactly at another interval's
start/end must still be counted as covered. Sorting `START` before `END`
at equal coordinates ensures the count is incremented for a newly starting
interval *before* any interval ending at that same coordinate is removed,
correctly reflecting inclusive endpoint semantics.

## Correctness check against handout example
`S = {(10,40),(20,60),(50,90),(15,70)}` — no point lies in all four
intervals, but the algorithm reports a maximum coverage of **3**, matching
the handout's stated example (`p = 50` lies in three intervals).
