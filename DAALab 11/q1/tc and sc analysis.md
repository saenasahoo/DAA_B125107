Time

The graph has 2V states, (v, p) with p ∈ {0,1}, and each edge gives 2 transitions, one per parity, so there are 2E transitions.
In 0-1 BFS the deque always holds distances d and d+1, so each state’s distance can be improved at most twice. That means each state is pushed at most twice, for at most 4V pops.
Each pop scans the adjacency list of u. Each (u, p) pops at most twice, so the total scanning is at most 2 · 2 · E = 4E.
The final combine min(d[v][0], d[v][1] + C) takes O(V).
Total: T(V, E) = O(V + E). There is no log factor because the deque replaces the priority queue.

Space

Adjacency list: O(V + E)
d[v][p]: O(2V) = O(V)
Deque: O(V), at most 4V pushes
Total: S = O(V + E)