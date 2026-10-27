Time

Initialization takes O(V) for the arrays and O(K) to enqueue the hubs.
Each vertex is enqueued at most once, because it is marked when dist[v] ≠ -1. That gives O(V) enqueues and dequeues.
Each dequeued vertex scans its adjacency list. Summed over all vertices this is Σdeg(v) = 2E for an undirected graph.
The tie-break check is O(1) per edge scan.
Total: T = O(V + E + K). Since K ≤ V, this is O(V + E).
It is far better than running K separate BFS passes, which would cost O(K · (V + E)).

Why the tie-break is correct: the queue is filled in hub-index order, so at every distance level the owners appear in non-decreasing order. The first discoverer of a vertex therefore has the smallest index, and the extra check handles any remaining equal-distance cases.

Space

Adjacency list: O(V + E)
dist, owner and the queue: O(V) each
Hub array: O(K)
Total: S = O(V + E)