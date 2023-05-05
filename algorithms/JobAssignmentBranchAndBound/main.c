#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    int worker;
    int job;
    int time;
} assign;

int **readFile(int *n)
{
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("file not found");
        return NULL;
    }
    fscanf(f, "%d", n);
    int **data = (int **)malloc(sizeof(int *) * (*n));
    int i, j;
    int weight;
    for (i = 0; i < *n; i++)
    {
        data[i] = (int *)malloc(sizeof(int) * (*n));
        for (j = 0; j < *n; j++)
        {
            fscanf(f, "%d", &weight);
            data[i][j] = weight;
        }
    }
    fclose(f);
    return data;
}
void printJobList(assign *assignList, int n)
{
    int i;
    int total = 0;
    for (i = 0; i < n; i++)
    {
        printf("worker %3d: ,job: %3d, time: %3d \n", assignList[i].worker, assignList[i].job, assignList[i].time);
        total += assignList[i].time;
    }

    printf("Total: %d\n", total);
}

int minIndex(int **data, int n, int row, int *jobList)
{
    int i;
    int min = INT_MAX;
    int minIndexx = -1;
    for (i = 0; i < n; i++)
    {
        if (min > data[row][i] && jobList[i] == 0)
        {
            min = data[row][i];
            minIndexx = i;
        }
    }
    return minIndexx;
}
void copyAssignList(assign *a, assign *b, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}
int lowerBoundRemain(int **data, int n, int worker, int *jobList)
{
    int i, j;
    int sum = 0;
    for (i = worker + 1; i < n; i++)
    {
        sum += data[i][minIndex(data, n, i, jobList)];
    }
    return sum;
}
void branchAndBoundJobAssignment(int **data, int n, int worker, int *jobList, assign *finalAssignList, assign *currentAssignList, int lowerBound, int currentTotalCost, int *temporaryMinTotalCost)
{
    if (lowerBound > *temporaryMinTotalCost)
        return;
    if (worker == n - 1)
    {
        if (*temporaryMinTotalCost >= currentTotalCost)
        {
            *temporaryMinTotalCost = currentTotalCost;
            currentAssignList[worker].worker = worker;
            currentAssignList[worker].job = minIndex(data, n, worker, jobList);
            currentAssignList[worker].time = data[worker][currentAssignList[worker].job];
            copyAssignList(finalAssignList, currentAssignList, n);
            return;
        }
    }

    int i;
    for (i = 0; i < n; i++)
    {
        if (jobList[i] == 1)
            continue;
        currentAssignList[worker].worker = worker;
        currentAssignList[worker].job = i;
        currentAssignList[worker].time = data[worker][i];
        jobList[i] = 1;
        int nextLowerBound = currentTotalCost + data[worker][i] + lowerBoundRemain(data, n, worker, jobList);
        int nextcurrentTotalCost = currentTotalCost + data[worker][i];
        branchAndBoundJobAssignment(data, n, worker + 1, jobList, finalAssignList, currentAssignList, nextLowerBound, nextcurrentTotalCost, temporaryMinTotalCost);
        /// reset state
        jobList[i] = 0;
    }
}
void initBranchAndBoundJobAssignment(int **data, int n)
{

    int *jobList = (int *)malloc(n * sizeof(int));

    int i;
    for (i = 0; i < n; i++)
    {

        jobList[i] = 0;
    }

    int temporaryTotalCost = INT_MAX;
    assign *finalAssignment = (assign *)malloc(sizeof(assign) * n);
    assign *currentAssignment = (assign *)malloc(sizeof(assign) * n);

    branchAndBoundJobAssignment(data, n, 0, jobList, finalAssignment, currentAssignment, lowerBoundRemain(data, n, -1, jobList), 0, &temporaryTotalCost);
    printJobList(finalAssignment, n);
}

int main()
{
    int n;
    int **data = readFile(&n);

    initBranchAndBoundJobAssignment(data, n);

    return 1;
}