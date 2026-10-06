9. Hu–Tucker (Garsia–Wachs simulation)

TC: Each merge reduces the sequence length by one, so the loop runs n−1 times. Each iteration has four O(n) steps: scanning for the first dip, deleting the pair, scanning left for the insertion point, and shifting to insert. That gives O(n) per iteration and O(n²) total.
Better bound: With a balanced search tree or Hu–Tucker's original data structures, it is O(n log n). Reading the input already needs Ω(n).
SC: O(n): the working sequence, 2n−1 tree nodes, and a recursion stack that is O(n) deep for a skewed tree.