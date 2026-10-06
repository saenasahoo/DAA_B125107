7. Minimise Deviation

TC:
Doubling odds and building the heap: O(n log n).
Halving phase: after doubling, every value is at most 2M, so each element can be halved at most log₂(2M) times before it turns odd. That is at most n·log M pops, each followed by a push at O(log n).
Total: O(n log n · log M) worst case.
Early exit: The loop stops as soon as the maximum is odd, so many inputs finish much sooner.
SC: O(n) for the heap.