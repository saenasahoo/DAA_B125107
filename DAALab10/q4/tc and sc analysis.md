Time

Building the adjacency list (CSR): one pass to count degrees, one prefix-sum pass and one fill pass, so O(V + E)
DSU initialisation: O(V)
Reverse loop over V vertices: each vertex is added once and each adjacency list is scanned once, so the neighbour work is Σ deg(v) = 2E. With union by size and path compression, each UNION and each FIND is O(α(V)) amortized (Tarjan’s bound; α is at most 4 in practice).
Reverse loop: O(V·α(V) + E·α(V))
Output: O(V)
Total: O((V+E)·α(V))
A naive approach recomputes components by BFS after every deletion, costing O(V·(V+E)). The reverse trick turns V deletions, which DSU cannot do, into V insertions, which it can.

Space

Adjacency list: 2E integers plus V+1 offsets, so O(V+E)
Edge copies eu, ev: O(E)
parent, size, sum, present, ans, p, w, deg: O(V)
Total: O(V+E)