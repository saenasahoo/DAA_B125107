1. Fractional Knapsack with Deterioration

TC: The while loop runs at most n times because each round permanently consumes one item. Round i scans the n−i+1 unused items, so the total is n + (n−1) + … + 1 = n(n+1)/2 = Θ(n²).
Best case: If every density is non-positive or W is exhausted after one item, it is O(n).
Why no sort: The density v/w − λt changes with t at a different rate for each item, so the order can change mid-run. A one-time sort therefore doesn't work.
SC: O(n) for the v, w, λ arrays and the used[] flags, plus O(1) scalars.