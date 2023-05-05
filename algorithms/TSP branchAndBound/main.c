#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    int start;
    int end;
    float length;
    int chosen;
} edge;

edge **readFile(int *n)
{
    FILE *f = fopen("dothi.txt", "r");
    if (f == NULL)
    {
        printf("file not found");
        return NULL;
    }
    fscanf(f, "%d", n);
    edge **matrix = (edge **)malloc(*n * sizeof(edge *));
    int i, j;
    float length;
    for (i = 0; i < *n; i++)
    {
        matrix[i] = (edge *)malloc(*n * sizeof(edge));
        for (j = 0; j < *n; j++)
        {
            fscanf(f, "%f", &length);
            matrix[i][j].length = length;
            matrix[i][j].start = i;
            matrix[i][j].end = j;
            matrix[i][j].chosen = 0;
        }
    }

    fclose(f);
    return matrix;
}

void printMaxtrix(edge **matrix, int n)
{
    int i, j;
    float total = 0;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (matrix[i][j].chosen == 1)
                total += matrix[i][j].length;
            printf("%5c%c: length: %5.2f, chosen: %5d\n", i + 65, j + 65, matrix[i][j].length, matrix[i][j].chosen);
        }
    }

    printf("Total: %.2f\n", total);
}

int hasThreeDegrees(int *degressList, int x)
{
    int i;
    return degressList[x] >= 2 ? 1 : 0;
}

int findRoot(int *parent, int x)
{
    while (x != parent[x])
    {
        x = parent[x];
    }
    return x;
}

int hasCircle(int *parent, int x, int y)
{
    return findRoot(parent, x) == findRoot(parent, y) ? 1 : 0;
}
void copyEdgeList(edge *a, edge *b, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {

        a[i] = b[i];
    }
}

float minEdgeLengthInMatrix(edge **matrix, int n)
{
    int i, j;
    float minLength = INT_MAX;
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (matrix[i][j].chosen == 1)
                continue;
            if (minLength > matrix[i][j].length)
                minLength = matrix[i][j].length;
        }
    }
    return minLength;
}
void branchAndBoundTSP(edge **matrix, int n, int u, float lowerBound, float currentTotalCost, float *tempMinCost, edge *currentAnswer, edge *finalAnswer, int *degreeList, int *parent)
{

    if (*tempMinCost <= lowerBound)
    {

        return;
    }
    if (u == n - 1)
    {
        int i;
        int a, b;
        a = b = -1;
        for (i = 0; i < n; i++)
        {
            if (degreeList[i] == 1)
            {
                if (a == -1)
                    a = i;
                else
                    b = i;
            }
        }
        if (currentTotalCost + matrix[a][b].length < *tempMinCost)
        {

            currentAnswer[u] = matrix[a][b];
            *tempMinCost = currentTotalCost + matrix[a][b].length;
            copyEdgeList(finalAnswer, currentAnswer, n);
        }
        return;
    }
    int i;
    for (i = 0; i < n; i++)
    {
        if (matrix[u][i].chosen == 1 || matrix[i][u].chosen == 1 || hasThreeDegrees(degreeList, i) || hasThreeDegrees(degreeList, u) || hasCircle(parent, u, i))
            continue;
        matrix[u][i].chosen = 1; // will reset
        matrix[i][u].chosen = 1; // will reset
        degreeList[i]++;         // will reset
        degreeList[u]++;         // will reset
        int rootI = findRoot(parent, i);
        int rootU = findRoot(parent, u);
        int resetRootI = parent[rootI];
        parent[rootI] = rootU; // will reset
        currentAnswer[u] = matrix[u][i];
        float nextLowerBound = currentTotalCost + matrix[u][i].length + (n - 1 - u) * minEdgeLengthInMatrix(matrix, n);
        float nextTotalCost = currentTotalCost + matrix[u][i].length;
        branchAndBoundTSP(matrix, n, u + 1, nextLowerBound, nextTotalCost, tempMinCost, currentAnswer, finalAnswer, degreeList, parent);
        matrix[u][i].chosen = 0; // will reset
        matrix[i][u].chosen = 0; // will reset
        degreeList[i]--;
        degreeList[u]--;
        parent[rootI] = resetRootI;
    }
}

void initBranchAndBoundTSP(edge **matrix, int n)
{

    float lowerBound = n * minEdgeLengthInMatrix(matrix, n);
    float tempMinCost = INT_MAX;
    edge *currentAnswer = (edge *)malloc(sizeof(edge) * n);
    edge *finalAnswer = (edge *)malloc(sizeof(edge) * n);
    int *degreeList = (int *)malloc(sizeof(int) * n);

    int *parent = (int *)malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++)
    {
        degreeList[i] = 0;
        parent[i] = i;
    }

    branchAndBoundTSP(matrix, n, 0, lowerBound, 0, &tempMinCost, currentAnswer, finalAnswer, degreeList, parent);

    // update for matrix

    for (i = 0; i < n; i++)
    {
        int u = finalAnswer[i].start;
        int v = finalAnswer[i].end;
        matrix[u][v].chosen = 1;
        matrix[v][u].chosen = 1;
    }

    printMaxtrix(matrix, n);
}

int main()
{
    int n;
    edge **matrix = readFile(&n);
    printMaxtrix(matrix, n);
    printf("--------------------------------\n");
    initBranchAndBoundTSP(matrix, n);
    return 1;
}