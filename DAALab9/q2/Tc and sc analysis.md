2. Huffman Coding

TC (heap version):
Heap build: O(n).
Merges: n−1 iterations, each with 2 extract-mins and 1 insert at O(log n), giving O(n log n).
Depth computation (one DFS): O(n).
Canonical sort by (length, symbol): O(n log n).
Code assignment: O(n) additions and shifts.
Total: O(n log n).
My C code: Each merge does a linear scan, so it is O(n²). Walking up the parent chain per leaf costs O(n·h) with h ≤ n−1, and the insertion sort is O(n²).
SC: O(n), since the tree has exactly 2n−1 nodes. The output codebook needs Σlen bits, which is O(n²) in the skewed worst case.