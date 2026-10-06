6. Reorganise String K Apart

TC:
Counting frequencies: O(n).
Initial heap build: O(σ log σ).
Main loop: n iterations, each with at most one push and one pop on a heap of size ≤ σ, so O(log σ) per iteration.
Total: O(n log σ), which is O(n) for a fixed alphabet (σ ≤ 256).
SC: O(n + σ) for the output string, the count array and the heap.
Idea behind the heap: A character is only pushed back after K positions, so the heap holds exactly the characters that are currently allowed.