#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    char name[100];
    float weight;
    float value;
    float valuePerWeight;
    int maxNumCanChoose;
    int pickNumber;
} thing;

thing *readFile(int *n, float *bagWeight)
{
    thing *thingList = (thing *)malloc(sizeof(thing));
    FILE *f = fopen("data.txt", "r");
    if (f == NULL)
    {
        printf("file not found");
        return NULL;
    }
    fscanf(f, "%f", bagWeight);
    int i = 0;
    while (!feof(f))
    {
        fscanf(f, "%f%f%d%[^\n]", &thingList[i].weight, &thingList[i].value, &thingList[i].maxNumCanChoose, &thingList[i].name);
        thingList[i].pickNumber = 0;
        thingList[i].valuePerWeight = thingList[i].value / thingList[i].weight;
        i++;
        thingList = realloc(thingList, sizeof(thing) * (i + 1));
    }
    *n = i;
    return thingList;
}

void printThingList(thing *thingList, int n, float bagWeight)
{
    int i;
    float total = 0;
    for (i = 0; i < n; i++)
    {
        printf("name: %-20s, weight: %10.2f, value: %10.2f, maxNumberCanChoose %10d,pickNumber: %10d\n", thingList[i].name, thingList[i].weight, thingList[i].value, thingList[i].maxNumCanChoose, thingList[i].pickNumber);
        total += thingList[i].pickNumber * thingList[i].value;
    }
    printf("\nBag weight: %.2f\n", bagWeight);
    printf("\nTotal value: %.2f\n", total);
}
void swap(thing *a, thing *b)
{
    thing temp = *a;
    *a = *b;
    *b = temp;
}
void bubbleSort(thing *thingList, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (thingList[j].valuePerWeight > thingList[j + 1].valuePerWeight)
                swap(&thingList[j], &thingList[j + 1]);
        }
    }
}
void copyArray(int *a, int *b, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

int min(int a, int b)
{
    return a > b ? b : a;
}
void branchAndBoundBalo(thing *thingList, int n, int thingIndex, float bagWeight, float upperBound, float currentTotalValue, float *temporaryMaxValue, int *currentAnswer, int *finalAnswer)
{
    if (upperBound < *temporaryMaxValue)
        return;
    int cases = bagWeight / thingList[thingIndex].weight;
    if (thingIndex == n - 1)
    {
        if (*temporaryMaxValue < currentTotalValue)
        {
            if (thingIndex == n - 1)
                currentAnswer[thingIndex] = min(thingList[thingIndex].maxNumCanChoose, cases);
            *temporaryMaxValue = currentTotalValue;
            copyArray(finalAnswer, currentAnswer, n);
        }
        // update the answer
    }
    int i;
    for (i = min(thingList[thingIndex].maxNumCanChoose, cases); i >= 0; i--)
    {
        float nextBagWeight = bagWeight - thingList[thingIndex].weight * i;
        float nextUpperBound = thingList[thingIndex].value * i + thingList[thingIndex + 1].valuePerWeight * nextBagWeight;
        float nextTotalValue = currentTotalValue + thingList[thingIndex].value * i;
        currentAnswer[thingIndex] = i;
        branchAndBoundBalo(thingList, n, thingIndex + 1, nextBagWeight, nextUpperBound, nextTotalValue, temporaryMaxValue, currentAnswer, finalAnswer);
    }
}

void initializeBranchAndBoundBalo(thing *thingList, int n, float bagWeight)
{
    int *currentAnswer = (int *)malloc(n * sizeof(int));
    int *finalAnswer = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        currentAnswer[i] = 0;
        finalAnswer[i] = 0;
    }
    float temporaryMaxValue = 0;
    branchAndBoundBalo(thingList, n, 0, bagWeight, thingList[0].valuePerWeight * bagWeight, 0, &temporaryMaxValue, currentAnswer, finalAnswer);
    for (i = 0; i < n; i++)
    {
        thingList[i].pickNumber = finalAnswer[i];
    }
}
int main()
{
    int n;
    float bagWeight;
    thing *thingList = readFile(&n, &bagWeight);
    printThingList(thingList, n, bagWeight);
    printf("\n");
    initializeBranchAndBoundBalo(thingList, n, bagWeight);
    printThingList(thingList, n, bagWeight);

    return 1;
}