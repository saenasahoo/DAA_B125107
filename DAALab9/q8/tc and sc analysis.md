8. Minimum Meeting Rooms

TC: The sort is O(n log n). The loop runs n times, with at most 1 pop and 1 push per meeting, each O(log k) where k is the heap size. Total: O(n log n).
Alternative: Sort starts and ends separately and use two pointers. It is still O(n log n) but needs no heap.
SC: The heap never holds more than the answer k (the number of rooms), so it is O(k), which is O(n) worst case when all meetings overlap. The input array itself is O(n).