# Q4 — Application of Sorting IV: Max Simultaneous People at a Party
**File:** `q4_max_people.c`

## Problem
Given entry time `a_i` and exit time `b_i` for `n` people (all `2n` times
distinct), find the time at which the most people are simultaneously
present.

## Algorithm — Sweep Line
1. Build `2n` events: `(a_i, +1)` (entry) and `(b_i, -1)` (exit).
2. Sort all events by time.
3. Sweep left to right, maintaining a running count; track the time at
   which the count is maximal.

## Time Complexity
| Step | Cost |
|---|---|
| Build `2n` events | O(n) |
| Sort `2n` events (`qsort`) | O(n log n) |
| Single sweep over `2n` events | O(n) |
| **Total** | **O(n log n)** |

## Space Complexity
- Events array of size `2n`: **O(n)**.
- `qsort`'s internal recursion stack: O(log n) typical.
- No other structures scale with `n`.
- **Total auxiliary space: O(n)**.

## Notes
- Since all `2n` times are distinct (per problem's no-ties assumption),
  no tie-breaking rule between simultaneous entry/exit events is needed —
  simplifying the comparator to a plain numeric sort on `time`.
