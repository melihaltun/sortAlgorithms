# sortAlgorithms
A selection of iterative and recursive sort algorithms

This code contains c and c++ implementations of some popular sort algorithms. 
The sort functions here can be categorized into two groups: 
1) Iterative sorts: bubble sort, insertion sort, selection sort, cocktail shaker sort, comp sort and heap sort
2) Recursive (divide and conquer) sorts: merge sort and quick sort

The code also contains quick select and median quick select algorithms.

Recursive sorts are preferred for their speed and iterative sorts are preferred for their space efficiency.
In general recursive sorts have O(n log n) time and O(n) space complexity whereas iterative sorts have O(n^2) time and O(1) space complexity.
However, heap and comb sort algorithms are exceptions to this generalization. Heap sort can be considered as an improved selection sort, and comb sort can be considered as an improved bubble sort. They are optimized such that they can achieve O(n log n) time complexity while retaining O(1) space complexity.

