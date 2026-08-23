# Q1 — Application of Sorting I: Sort by Colour
**File:** `q1_sort_by_colour.c`

## Problem
Given `n` pairs `(number, colour)` already sorted by `number`, produce an
order with all REDs before all BLUEs before all YELLOWs, keeping numbers
sorted within each colour.

## Algorithm
Single pass: place each item into one of 3 buckets (RED, BLUE, YELLOW) in
the order encountered, then concatenate RED + BLUE + YELLOW.
Because the input is already sorted by `number` and we only append to
buckets (never reorder within a bucket), each bucket stays sorted — this
is a 3-way **stable bucket/counting partition**.

## Time Complexity
| Step | Cost |
|---|---|
| Pass 1: distribute `n` items into 3 buckets | O(n) |
| Pass 2: concatenate 3 buckets (total size n) | O(n) |
| **Total** | **O(n)** |

No comparisons or sorting are needed because the colour domain is
constant-size (3) and the numeric order is inherited "for free" from the
already-sorted input.

## Space Complexity
- 3 auxiliary buckets holding all `n` items in total → **O(n)** extra space.
- Output array of size `n` → **O(n)**.
- Overall auxiliary space: **O(n)**. (In-place O(1)-extra variants exist
  using a 3-way Dutch National Flag partition, but they do not preserve
  numeric order without the sorted-input assumption exploited here.)

## Why this meets the O(n) requirement
A general comparison sort would cost O(n log n). We beat that bound only
because:
1. The colour alphabet size is O(1) (3 colours) → counting/bucket sort applies.
2. The input's existing numeric order removes any need to re-sort within
   a bucket — a single stable pass suffices.
