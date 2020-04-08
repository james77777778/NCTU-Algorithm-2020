# Sorting Algorithm
## Testing Scenario
0. i7-8700K CPU @ 3.70GHz
1. array size = 10000
2. random integar within range [-100, 100]

## Comparison Table
Algorithm      | Time Complexity  | Time | Note |
---------------|:-----------------|------|------|
Bubble Sort    | |789.736 ms
Selection Sort | |213.147 ms
Insertion Sort | |120.945 ms
Recursive Quick Sort     | |1.413 ms | using tail recursive is fast
Iterative Quick Sort     | |1.541 ms
Recursive Merge Sort     | |8.742 ms
Heap Sort      | |2.406 ms
Counting Sort  | |0.173 ms
Radix Sort (64 based)    | |0.610 ms | slower than counting sort because data range is small