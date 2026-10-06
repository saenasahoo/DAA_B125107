4. Minimum Cost to Connect Sticks

TC: There are n−1 merges. The heap size shrinks from n to 1, so the work is Σ 3·log k for k = n down to 2 = O(log n!) = Θ(n log n).
Optimisation: After sorting, two queues (original sorted sticks plus a FIFO of merged sums) replace the heap. The loop becomes O(n), though the sort keeps the total at O(n log n).
SC: O(n) for the heap.
Note: The total cost can reach about n·ΣL, so use long long.