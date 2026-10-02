Time: The table has (m+1)(n+1) cells, each computed in O(1) as a min of three values, so Θ(mn). The traceback starts at (m,n) and each step reduces i, j, or both, so it needs at most m+n steps. Total: Θ(mn).
Space: The table D takes Θ(mn). The printed edit script has at most m+n operations.
Trade-off: For the distance alone, two rows give O(min(m,n)) space. The traceback needs the full table (or Hirschberg's technique for O(m+n) space at about 2× time).
Bounds: The distance always lies between |m−n| and max(m,n).