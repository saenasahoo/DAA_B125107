Time

Initialising N = R·C cells: O(R·C)
Per land addition: flatten the coordinate in O(1), check 4 neighbours in O(1), and do at most 4 UNIONs. With union by size and path compression, each UNION or FIND is O(α(RC)) amortized (Tarjan’s bound; α is at most 4 in practice).
Over K additions: O(K·α(RC)). A repeated cell is only an O(1) check.
Total: O(R·C + K·α(R·C))
Without DSU, recounting islands by BFS/DFS after every operation would cost O(K·R·C). DSU removes the factor of K.

Space

parent, size: 2·R·C integers; land: R·C bytes
Total: O(R·C)