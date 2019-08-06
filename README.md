# Machine Learning: Hierarchical Clustering Algorithm
What is Hierarchical Clustering?: <br/>
https://towardsdatascience.com/understanding-the-concept-of-hierarchical-clustering-technique-c6e8243758ec

## How to Compile and Run
Assuming you have installed the [MinGW Compiler](http://www.mingw.org/) or are using a terminal that comes with it, such as [Cygwin](https://www.cygwin.com/), the project can be compiled by running `g++ main.cpp -o main.exe` and run by running `./main.exe`.

The begining of the resulting output should look like: <br/>
```
===============================================================================
            Running Hierarchical Clustering for Single Linkage:
===============================================================================

------------------------------------------
Merging (A4, ) with (A5, ). Distance/similarity between clusters is = 1.01.
------------------------------------------

With 11 clusters:
Cluster 1 = A1,
Cluster 2 = A2,
Cluster 3 = A3,
Cluster 4 = A4, A5,
Cluster 5 = A6,
Cluster 6 = A7,
Cluster 7 = A8,
Cluster 8 = A9,
Cluster 9 = A10,
Cluster 10 = A11,
Cluster 11 = A12,

------------------------------------------
Merging (A10, ) with (A11, ). Distance/similarity between clusters is = 1.01.
------------------------------------------

With 10 clusters:
Cluster 1 = A1,
Cluster 2 = A2,
Cluster 3 = A3,
Cluster 4 = A4, A5,
Cluster 5 = A6,
Cluster 6 = A7,
Cluster 7 = A8,
Cluster 8 = A9,
Cluster 9 = A10, A11,
Cluster 10 = A12,

------------------------------------------
Merging (A1, ) with (A2, ). Distance/similarity between clusters is = 1.01.
------------------------------------------

With 9 clusters:
Cluster 1 = A1, A2,
Cluster 2 = A3,
Cluster 3 = A4, A5,
Cluster 4 = A6,
Cluster 5 = A7,
Cluster 6 = A8,
Cluster 7 = A9,
Cluster 8 = A10, A11,
Cluster 9 = A12,
```
