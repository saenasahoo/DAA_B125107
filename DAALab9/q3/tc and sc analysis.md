3. Minimum Refuelling Stops

TC:
Sorting: O(n log n).
Heap work: each station is pushed at most once and popped at most once, and each operation costs O(log n). The number of stops is at most n, so the whole loop is O(n log n).
Total: O(n log n), dominated by the sort and the heap work equally.
SC: O(n) for the sorted array and the heap, which can hold every reachable station.