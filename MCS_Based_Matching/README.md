# MCS-Based String Matching Algorithm

## Overview
This folder contains the implementation of the **MCS (Minimum Common Subsequence)-Based String Matching Algorithm**. This method leverages lossy MCSs to optimize pattern matching by reducing redundant comparisons, leading to significant efficiency improvements over the naive approach.

### Key Concepts:
- **Lossy MCSs**: Precomputed binary strings with a specific number of ones to maximize overlap and minimize redundant comparisons.
- **Efficiency**: Reduces the number of comparisons in the pattern matching process, making it more efficient for large texts.

### Performance
- The time complexity for generating lossy MCSs is higher than the naive method, but the overall search process is faster, especially for larger datasets.

## Files
- **mcs_based_matching.cpp**: C++ implementation of the MCS-based string matching algorithm.
- **Report.docx**: Report with detailed explanation, analysis, and results.

  
## How to Run
1. Compile the code using:
   ```bash
   g++ mcs_based_matching.cpp -o mcs_based_matching
