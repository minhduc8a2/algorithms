#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    char name[100];
    int weight;
    float value;
    int pickNumber;
} thing;

thing *readFile(int *n, int *bagWeight)
{
    thing *thingList = (thing *)malloc(sizeof(thing));
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("file not found");
        return NULL;
    }
    fscanf(f, "%d", bagWeight);
    int i = 0;
    while (!feof(f))
    {
        fscanf(f, "%d%f%[^\n]", &thingList[i].weight, &thingList[i].value, &thingList[i].name);
        thingList[i].pickNumber = 0;
        i++;
        thingList = realloc(thingList, sizeof(thing) * (i + 1));
    }
    *n = i;
    return thingList;
}
void makeTable(thing *thingList, int n, int bagWeight, float **valueTable, int **numberTable)
{

    int i;

    for (i = 0; i < n; i++)
    {
        valueTable[i] = (float *)malloc((bagWeight + 1) * sizeof(float));
        numberTable[i] = (int *)malloc((bagWeight + 1) * sizeof(int));
    }

    for (i = 0; i < bagWeight + 1; i++)
    {
        numberTable[0][i] = i / thingList[0].weight;
        valueTable[0][i] = numberTable[0][i] * thingList[0].value;
    }

    int j, k;
    int highestValue, thingNumber;
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < bagWeight + 1; j++)
        {
            int timesOfRepeat = j / thingList[i].weight;
            thingNumber = 0;
            highestValue = valueTable[i - 1][j - 0 * thingList[i].weight] + 0 * thingList[i].value;
            for (k = 1; k < timesOfRepeat; k++)
            {
                if (valueTable[i - 1][j - k * thingList[i].weight] + k * thingList[i].value > highestValue)
                {
                    highestValue = valueTable[i - 1][j - k * thingList[i].weight] + k * thingList[i].value;
                    thingNumber = k;
                }
            }
            valueTable[i][j] = highestValue;
            numberTable[i][j] = thingNumber;
        }
    }
}
void printTables(float **valueTable, int **numberTable, thing *thingList, int n, int bagWeight)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("%-20s", thingList[i].name);
        for (j = 0; j < bagWeight + 1; j++)
        {
            printf("||%.2f - %d || ", valueTable[i][j], numberTable[i][j]);
        }
        printf("\n");
    }
}
void lookForAnswer(int **numberTable, thing *thingList, int n, int bagWeight)
{
    int i;
    for (i = n - 1; i >= 0; i--)
    {
        thingList[i].pickNumber = numberTable[i][bagWeight];
        bagWeight -= thingList[i].pickNumber * thingList[i].weight;
    }
}
void printThingList(thing *thingList, int n, int bagWeight)
{
    int i;
    int total = 0;
    for (i = 0; i < n; i++)
    {
        printf("name: %-20s, weight: %10d, value: %10.2f, pickNumber: %10d\n", thingList[i].name, thingList[i].weight, thingList[i].value, thingList[i].pickNumber);
        total += thingList[i].pickNumber * thingList[i].value;
    }
    printf("\nBag weight: %d\n", bagWeight);
    printf("\nTotal value: %d\n", total);
}
void dynamicBag(thing *thingList, int n, int bagWeight)
{
    float **valueTable;
    int **numberTable;
    valueTable = (float **)malloc(n * sizeof(float *));
    numberTable = (int **)malloc(n * sizeof(int *));
    makeTable(thingList, n, bagWeight, valueTable, numberTable);
    // printTables(valueTable, numberTable, thingList, n, bagWeight);
    lookForAnswer(numberTable, thingList, n, bagWeight);
    printThingList(thingList, n, bagWeight);
}

int main()
{
    int n;
    int bagWeight;
    thing *thingList = readFile(&n, &bagWeight);
    printThingList(thingList, n, bagWeight);
    printf("\n");
    dynamicBag(thingList, n, bagWeight);
    return 1;
}