Time

Reading A, filling pos, DSU initialisation: O(n)
m UNIONs: with union by size and path compression, each is O(α(n)) amortized (Tarjan’s bound; α is at most 4 in practice), so O(m·α(n))
Computing block offsets (one FIND per position): O(n·α(n))
Value scan v = 1..n (one FIND each): O(n·α(n))
Position scan i = 1..n (one FIND each): O(n·α(n))
Total: O((n+m)·α(n))
Because the values are exactly 1..n, scanning them in increasing order puts each component’s values in sorted order automatically. The usual alternative sorts each component, which costs O(n log n) overall, so bucketing saves the log factor.

Space

A, pos, parent, size, off, fill, ptr, vals: about 8n integers
Total: O(n)