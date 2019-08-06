// The Machine Learning Hierarchical Clustering Algorithm
// By: Karen Proft
// Semptember 27, 2018


#include <iostream>
#include <array>
#include <math.h>
#include <algorithm>

using namespace std;

// Calculates the distance/similarity between two vectors/clusters
float calculateDistance(float s[12][2], int a, int b)
{
    float distance = pow(s[a][0] - s[b][0], 2) + pow(s[a][1] - s[b][1], 2); //(x1 - x2)^2 + (y1 - y2)^2
    distance = (float) sqrt(distance);

    return distance;
}

// Only used in the first iterations to calculate all the distances/similarities between each vector
void calculateAllDistances(float s[12][2], float dArray[12][12])
{
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            dArray[i][j] = calculateDistance(s, i, j);
        }
    }
}

// Searches a 2d array for it's smallest value and returns the index of that location through the x and y parameters
// and it's distance through the returned minDistance variable
float findSmallestDistance(float dArray[12][12], int &x, int &y)
{
    float minDistance = -1;
    // Set min distance to a distance in the matrix that is not 0
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (dArray[i][j] != 0)
            {
                minDistance = dArray[i][j];
                x = i;
                y = j;
            }
        }
    }

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if ((dArray[i][j] < minDistance) && (dArray[i][j] != 0))
            {
                minDistance = dArray[i][j];
                x = i;
                y = j;
            }
        }
    }

    return minDistance;
}

// Single linkage combination
void recalculateDistancesBasedOnMin(float dArray[12][12], int x, int y)
{
    for (int i = 0; i < 12; i++)
    {
        //If the distance from x vector is smaller then it is kept, else it is changed
        //to the y vector's distance as it is smaller
        if((dArray[i][x] > dArray[i][y]) && (dArray[i][y] != 0))
        {
            dArray[x][i] = dArray[i][y];
            dArray[i][x] = dArray[i][y];
        }
    }
}

// Complete linkage combination
void recalculateDistancesBasedOnMax(float dArray[12][12], int x, int y)
{
    for (int i = 0; i < 12; i++)
    {
        //If the distance from x vector is bigger then it is kept, else it is changed
        //to the y vector's distance as it is larger
        if((dArray[i][x] < dArray[i][y]) && (dArray[i][x] != 0))
        {
            dArray[x][i] = dArray[i][y];
            dArray[i][x] = dArray[i][y];
        }
    }
}

// Sets a vector/group as no longer active in the k array and makes all of it's values zero in the 2d distance array,
// as it now belongs in a new cluster and its distance is being kept by the row/column for that new cluster
void deactivateAPoint(float dArray[12][12], int y, int k[12])
{
    for (int i = 0; i < 12; i++)
    {
        dArray[y][i] = 0;
        dArray[i][y] = 0;
    }
    k[y] = 1;
}

//Merges two clusters together in the cluster matrix
void addToClusterMatrix(int cMatrix[12][12], int c, int x, int y)
{
    //Find which cluster x currently belongs to
    int xCluster = x;
    for(int i = 0; i <12; i++)
    {
        if (cMatrix[i][x] == 1)
        {
            xCluster = i;
        }
    }

    //Find which cluster Y currently belongs to
    int yCluster = y;
    for(int i = 0; i <12; i++)
    {
        if (cMatrix[i][y] == 1)
        {
            yCluster = i;
        }
    }

    //Move all points in y's cluster into x's cluster
    for (int i = 0; i < 12; i++)
    {
        if(cMatrix[yCluster][i] == 1)
        {
            cMatrix[xCluster][i] = 1;
            cMatrix[yCluster][i] = 0;
        }
    }
}

//Sets up starting cluster matrix and the cluster active/inactive array
void initializeClusterMatrix(int cMatrix[12][12], int k[12])
{
    for (int i = 0; i < 12; i++)
    {
        //Reactivate all clusters
        k[i] = 0;
        for (int j = 0; j < 12; j++)
        {
            //Each vector belongs in its own individual cluster
            if (i == j)
            {
                cMatrix[i][j] = 1;
            }
            else
            {
                cMatrix[i][j] = 0;
            }
        }
    }
}

//Prints which vectors belong in which cluster
void printClusterOutput(int clusterMatrix[12][12], int c, int k[12])
{
    cout << "With " << c << " clusters: \n";

    int clusterNumber = 1;
    for (int i = 0; i < 12; i++)
    {
        if (k[i] == 0) //Cluster row in matrix is active
        {
            cout << "Cluster " << clusterNumber << " = ";
            for (int j = 0; j < 12; j++)
            {
                if (clusterMatrix[i][j] == 1)
                {
                    cout << "A" << j + 1 << ", ";
                }
            }
            cout << "\n";
            clusterNumber++;
        }
    }
}

//Prints which two cluster were just merged
void printMergedClusters(int clusterMatrix[12][12], int k[12], float distance, int x, int y)
{

    cout << "\nMerging ";
    //Find which cluster x currently belongs to
    int xCluster = x;
    for(int i = 0; i <12; i++)
    {
        if (clusterMatrix[i][x] == 1)
        {
            xCluster = i;
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (i == 0)
        {
            cout << "(";
        }
        if (clusterMatrix[xCluster][i] == 1)
        {
            cout << "A" << i + 1 << ", ";
        }
        if (i == 11)
        {
            cout << ")";
        }
    }

    cout << " with ";
    //Find which cluster Y currently belongs to
    int yCluster = y;
    for(int i = 0; i <12; i++)
    {
        if (clusterMatrix[i][y] == 1)
        {
            yCluster = i;
        }
    }

    for (int i = 0; i < 12; i++)
    {
        if (i == 0)
        {
            cout << "(";
        }
        if (clusterMatrix[yCluster][i] == 1)
        {
            cout << "A" << i + 1 << ", ";
        }
        if (i == 11)
        {
            cout << ")";
        }

    }

    cout << ". Distance/similarity between clusters is = " << distance << ".\n";
}

int main()
{
    // Initialize Variables
    float s[12][2] = {{2, 2}, //All the samples/vectors
                  {3.01, 2},
                  {4.02, 2},
                  {5.03, 2},
                  {6.04, 2},
                  {7.05, 2},
                  {2, 3.5},
                  {3.01, 3.5},
                  {4.02, 3.5},
                  {5.03, 3.5},
                  {6.04, 3.5},
                  {7.05, 3.5}};
    int k[12]; //Keeps track of active clusters, 0 = active, 1 = inactive
    float distancesArray[12][12]; //The matrix of distances between each point/set of clusters
    int clusterMatrix[12][12]; //Keeps track the clusters there are and which vector belongs in which cluster

    //Run the algorithm
    int x;
    int y;
    float minDistance;
    float maxDistance;
    for (int linkageType = 0; linkageType < 2; linkageType++)
    {
        //Calculate all initial distances between vectors and initialize cluster matrix
        calculateAllDistances(s, distancesArray);
        initializeClusterMatrix(clusterMatrix, k);

        if (linkageType == 0)
        {
            cout << "===============================================================================\n";
            cout << "            Running Hierarchical Clustering for Single Linkage:";
            cout << "\n===============================================================================\n";
        }
        else if (linkageType == 1)
        {
            cout << "\n\n===============================================================================\n";
            cout << "            Running Hierarchical Clustering for Complete Linkage:";
            cout << "\n===============================================================================\n";
        }

        //Repeat clustering until all points have been added to one big cluster
        for (int c = 11; c >= 1; c--)
        {

            minDistance =  findSmallestDistance(distancesArray, x, y);
            cout << "\n------------------------------------------";
            printMergedClusters(clusterMatrix, k, minDistance, x, y);
            cout << "------------------------------------------\n\n";

            //For single linkage only
            if (linkageType == 0)
            {
                recalculateDistancesBasedOnMin(distancesArray, x, y);
            }

            //For complete linkage only
            else if (linkageType == 1)
            {
                recalculateDistancesBasedOnMax(distancesArray, x, y);
            }

            deactivateAPoint(distancesArray, y, k);

            //Adjust cluster matrix to keep track of which vector is in which cluster
            addToClusterMatrix(clusterMatrix, c, x, y);
            printClusterOutput(clusterMatrix, c, k);
        }
    }

    return 0;
}
