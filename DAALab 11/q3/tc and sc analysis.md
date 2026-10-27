Let N = number of words and L = word length.

Time

Building the hash table: N insertions at O(L) each for hashing, so O(N·L).
Each word is visited at most once overall, because the side[] marks prevent revisits.
Expanding one word means L positions × 25 replacement characters = 25L candidate words. Each candidate needs an O(L) hash computation plus an O(L) string comparison, with expected O(1) probes at a low load factor. That is O(25·L·L) = O(L²) per word.
Total: T = O(N·L²), which is about 1e5 × 100 × 25 ≈ 2.5e7 lookups in the worst case with L = 10.
Compare this to a naive pairwise Hamming check, which is O(N²·L).
Bidirectional advantage: with branching factor b and shortest-path length d, a one-way BFS visits O(bᵈ) nodes. Bidirectional BFS meets in the middle and visits only O(2·b^(d/2)). The worst-case bound is unchanged, but it is much faster in practice.

Space

Word storage: O(N·L)
Hash table: O(N) slots, which is 2¹⁸ here
side, dist and the two queues: O(N) each
Total: S = O(N·L)