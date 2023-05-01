#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    float length;
    int startVertex, endVertex;
    int chosen;

} edge;

edge *readFile(int *n, int *k)
{
    FILE *f = fopen("dothi.txt", "r");
    if (f == NULL)
    {
        printf("File not found");
        return NULL;
    }
    fscanf(f, "%d", n);
    edge *edgeList = (edge *)malloc(sizeof(edge));
    int i, j;
    float length;

    for (i = 0; i < *n; i++)
    {
        for (j = 0; j < *n; j++)
        {
            fscanf(f, "%f", &length);
            if (length != 0 && j >= i)
            {
                edgeList[*k].startVertex = i;
                edgeList[*k].endVertex = j;
                edgeList[*k].length = length;
                edgeList[*k].chosen = 0;
                *k += 1;
                edgeList = realloc(edgeList, sizeof(edge) * (*k + 1));
            }
        }
    }
    fclose(f);
    return edgeList;
}

void printEdgeList(edge *edgeList, int k)
{
    int i;
    printf("Edge list: \n");
    for (i = 0; i < k; i++)
    {
        printf("startVertex: %d, endVertex: %d, length: %f, chosen: %d\n", edgeList[i].startVertex, edgeList[i].endVertex, edgeList[i].length, edgeList[i].chosen);
    }
}
void swap(edge *a, edge *b)
{
    edge temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(edge *edgeList, int k)
{
    int i, j;
    for (i = 0; i < k - 1; i++)
    {
        for (j = 0; j < k - i - 1; j++)
        {
            if (edgeList[j].length > edgeList[j + 1].length)
                swap(&edgeList[j], &edgeList[j + 1]);
        }
    }
}

int hasThreeDegrees(int *degreeList, int x)
{
    return degreeList[x] >= 2 ? 1 : 0;
}
int findRoot(int *parentList, int x)
{
    while (x != parentList[x])
    {
        x = parentList[x];
    }
    return x;
}
int hasCircle(int *parentList, int u, int v)
{
    return findRoot(parentList, u) == findRoot(parentList, v) ? 1 : 0;
}

float greedy(edge *edgeList, int k, int n)
{
    bubbleSort(edgeList, k);
    int *parentList = (int *)malloc(n * sizeof(int));
    int *degreeList = (int *)malloc(n * sizeof(int));
    int *chosenVertexList = (int *)malloc(n * sizeof(int));
    float cost = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        degreeList[i] = 0;
        chosenVertexList[i] = 0;
        parentList[i] = i;
    }

    for (i = 0; i < k; i++)
    {
        if (!hasCircle(parentList, edgeList[i].startVertex, edgeList[i].endVertex) && !hasThreeDegrees(degreeList, edgeList[i].startVertex) && !hasThreeDegrees(degreeList, edgeList[i].endVertex))
        {
            edgeList[i].chosen = 1;
            degreeList[edgeList[i].startVertex]++;
            degreeList[edgeList[i].endVertex]++;
            cost += edgeList[i].length;
            parentList[findRoot(parentList, edgeList[i].endVertex)] = findRoot(parentList, edgeList[i].startVertex);
        }
    }
    int start, end;
    start = end = -1;

    for (i = 0; i < n; i++)
    {

        if (degreeList[i] == 1)
        {
            if (start == -1)
                start = i;
            else
                end = i;
        }
    }

    for (i = 0; i < k; i++)
    {
        if ((edgeList[i].startVertex == start && edgeList[i].endVertex == end) || (edgeList[i].startVertex == start && edgeList[i].endVertex == end))
        {
            edgeList[i].chosen = 1;
            cost += edgeList[i].length;
        }
    }
    return cost;
}
int main()
{
    int n;
    int k = 0;
    edge *edgeList = readFile(&n, &k);
    float cost = greedy(edgeList, k, n);
    // bubbleSort(edgeList, k);
    printEdgeList(edgeList, k);
    printf("Cost:%9.2f\n", cost);
    return 1;
}