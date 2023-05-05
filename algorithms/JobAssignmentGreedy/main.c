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
void greedy(int **data, int n, assign *assignList)
{

    int *jobList = (int *)malloc(n * sizeof(int));

    int i;
    for (i = 0; i < n; i++)
    {

        jobList[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        assignList[i].worker = i;
        int minTimeJob = minIndex(data, n, i, jobList);
        assignList[i].job = minTimeJob;
        assignList[i].time = data[i][minTimeJob];
        jobList[minTimeJob] = 1;
    }
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

int main()
{
    int n;
    int **data = readFile(&n);
    assign *assignList = (assign *)malloc(sizeof(assign) * n);
    greedy(data, n, assignList);
    printJobList(assignList, n);
    return 1;
}