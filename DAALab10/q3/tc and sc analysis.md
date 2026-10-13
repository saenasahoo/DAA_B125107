Time

DSU initialisation: O(V)
Initial pushes of V singletons into the heap: O(V log V). Building the heap in one pass would make this O(V).
Per edge: two FINDs and an O(1) merge. With union by size and path compression, each FIND is O(α(V)) amortized (Tarjan’s bound; α is at most 4 in practice). Over E edges this is O(E·α(V)).
Heap pushes happen only on a successful merge, so there are at most V−1 of them, each O(log V): O(V log V) in total.
Lazy deletion: every heap entry is popped at most once. The heap holds at most V + (V−1) < 2V entries, so total pop cost is O(V log V). The validity check on the top entry is O(1).
Total: O(V log V + E·α(V))
This is within the looser bound O((V+E) log(V+E)) quoted in the code comment, but tighter.

Space

parent, size, sum: O(V)
Heap: at most 2V entries, so O(V). The code allocates V+E+1 slots for safety, which is O(V+E) in practice; allocating 2V would give O(V).
Total: O(V)