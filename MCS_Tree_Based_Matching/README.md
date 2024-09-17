
# Lab 2: MCS Tree-Based Matching Algorithm

## Overview
This folder contains the implementation of the **MCS Tree-Based Matching Algorithm**. Building upon the work in Lab 1, this approach organizes lossy MCSs into a binary tree structure, allowing for more efficient pattern matching by traversing the tree structure.

### Key Concepts:
- **MCS Trees**: A tree data structure where the branches represent binary strings (MCSs), improving search efficiency.
- **Text Tree Generation**: The algorithm generates trees for each substring of the text based on the structure of the MCS tree.
- **Efficiency**: The MCS tree-based algorithm is more efficient than both the naive and the standard MCS-based approach for large-scale pattern matching.

### Performance
- While the MCS tree construction adds some initial overhead, the matching process is significantly faster due to tree traversal optimizations.

## Files
- **mcs_tree_based_matching.cpp**: The source code for the MCS tree-based matching algorithm.
- **Report.docx**: A detailed report explaining the algorithm, providing performance analysis, and comparing it with the naive and MCS-based approaches.

## How to Run
1. Compile the code using:
   ```bash
   g++ mcs_tree_based_matching.cpp -o mcs_tree_based_matching
