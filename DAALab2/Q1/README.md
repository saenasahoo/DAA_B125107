# Dictionary Operations: Time Complexity Comparison

This question analyzes the asymptotic worst-case running times of the seven primary dictionary operations for different data structures.

## Dictionary Operations

The following operations are considered:

- **Search(D, k)** – Given a search key `k`, find the element in dictionary `D` whose key is `k`.
- **Insert(D, x)** – Insert a data item `x` into dictionary `D`.
- **Delete(D, x)** – Given a pointer to data item `x`, remove it from dictionary `D`.
- **Max(D)** – Retrieve the item with the largest key.
- **Min(D)** – Retrieve the item with the smallest key.
- **Predecessor(D, x)** – Retrieve the item whose key is immediately before `x` in sorted order.
- **Successor(D, x)** – Retrieve the item whose key is immediately after `x` in sorted order.

## Data Structures

The operations are analyzed for the following six data structures:

1. Unsorted Array
2. Sorted Array
3. Singly Linked Unsorted List
4. Singly Linked Sorted List
5. Doubly Linked Unsorted List
6. Doubly Linked Sorted List

## Time Complexity

| Data Structure | Search | Insert | Delete | Min | Max | Predecessor | Successor |
|---|---:|---:|---:|---:|---:|---:|---:|
| Unsorted Array | O(n) | O(1) | O(1)* | O(n) | O(n) | O(n) | O(n) |
| Sorted Array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1)** | O(1)** |
| Singly Linked Unsorted List | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(1) |
| Singly Linked Sorted List | O(n) | O(n) | O(n) | O(1) | O(n) | O(n) | O(1) |
| Doubly Linked Unsorted List | O(n) | O(1) | O(1)* | O(n) | O(n) | O(1) | O(1) |
| Doubly Linked Sorted List | O(n) | O(n) | O(1)* | O(1) | O(1) | O(1) | O(1) |

### Notes

- `*` Delete is O(1) when a direct pointer to the item is already available, as specified in the question. For an unsorted array, the item can be swapped with the last element and the array size reduced. In a doubly linked list, the `prev` and `next` pointers allow direct unlinking.
- `**` For a sorted array, predecessor and successor are O(1) when the index of the item is already known. If only the key is given, finding the index first requires O(log n) binary search.

## Program and Files

```text
Q1/
├── q1.c
├── results.csv
├── plot_results.py
├── all_operations.png
├── per_structure.png
└── README.md
```

### File Description

- `q1.c` – C program implementing and benchmarking the dictionary operations.
- `results.csv` – Contains the experimental timing results.
- `plot_results.py` – Python script used to generate the plots.
- `all_operations.png` – Plot comparing the operations.
- `per_structure.png` – Plot showing results for the different data structures.
- `README.md` – Documentation for Question 1.

## Objective

The objective is to determine the worst-case asymptotic running time of the seven dictionary operations for each data structure and experimentally validate the theoretical results by plotting their order of growth.

## Result

The program records the running times for different input sizes in `results.csv`. The results are plotted using Python to compare the order of growth of the operations and data structures.
