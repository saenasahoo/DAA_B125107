10. Greedy Superstring

TC (my C code):
Overlap check for one pair costs O(L²), because it tries each k and compares up to k characters.
Each round examines O(n²) pairs, so one round is O(n²L²), and there are n−1 rounds, giving about O(n³L²).
Merged strings grow up to nL, which makes the real worst case slightly higher.
TC (optimised):
KMP overlap for all ordered pairs: O(n²L).
Sort all overlaps: O(n² log n).
Greedily link pairs, using each string at most once as a left side and once as a right side, with cycle checks: O(n²).
Total: O(n²(L + log n)).
SC: O(nL) for the strings, plus O(n²) for the overlap table in the optimised version.
Context: Finding the exact shortest superstring is NP-hard, so there is no polynomial-time exact algorithm to compare against. This greedy is a heuristic, and the 2-approximation claim is the open conjecture in your question.