# DAA Lab-6, Q4: Matrix Chain Multiplication (DP) — Time & Space Complexity

## Time Complexity
There are O(N²) subproblems dp[i][j], and each subproblem is solved by trying O(N) possible split points k. This gives an overall time complexity of **O(N³)**.

## Space Complexity
A 2-D dp table of size N x N is used to store the minimum cost for every subchain, giving a space complexity of **O(N²)**.
