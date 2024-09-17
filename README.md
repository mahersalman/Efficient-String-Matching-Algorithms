# MCS-Based String Matching Algorithms

This repository contains two distinct approaches for string matching based on MCS (Minimum Common Subsequence). Both algorithms aim to improve the efficiency of pattern matching over large datasets by leveraging MCS structures and are compared with a naive string matching algorithm.

## Approaches Overview

1. **MCS-Based String Matching (First Approach)**:
   - This approach utilizes lossy MCSs to optimize the string matching process by reducing the number of redundant comparisons.
   - Lossy MCSs are precomputed binary sequences designed to maximize overlap in patterns.
   - **MCS** stands for **Minimum Common Subsequence**, representing the minimal matching subsequences extracted from a given text.
   - This approach offers significant improvements over the naive algorithm, especially for larger datasets.

2. **MCS Tree-Based Matching (Second Approach)**:
   - An extension of the first approach, the second method organizes lossy MCSs into a tree structure, further improving the efficiency of the matching process.
   - By storing the MCSs in a tree, the algorithm can traverse the structure for quicker comparisons, resulting in faster pattern matching.
   
### Comparison with Naive Algorithm
- The **naive algorithm** compares each possible substring of the text with the pattern, leading to a time complexity of **O(n * m)**, where `n` is the length of the text and `m` is the length of the pattern.
- Both the MCS-based and MCS tree-based approaches are designed to reduce this complexity:
  - **MCS-Based Approach**: Precomputes lossy MCSs, which adds initial overhead but significantly reduces comparisons.
  - **MCS Tree-Based Approach**: Further optimizes the process by organizing MCSs in a tree structure, making the search faster than both the naive and MCS-based approaches.

## Folder Structure
- **MCS_Based_Matching**: Implements the first approach of MCS-based string matching using lossy MCSs.
- **MCS_Tree_Based_Matching**: Implements the second approach with MCSs organized in a tree structure for optimized matching.

## How to Run
1. Navigate to each folder for specific instructions.
2. Compile and run the code as described in the respective README files.

## Author
Maher Salman
