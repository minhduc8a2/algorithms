#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef struct
{
    char name[20];
    float weight;
    float value;
    float valuePerWeight;
    int pickedNumber;
} thing;

thing *ReadFile(float *bagWeight, int *n)
{
    FILE *f = fopen("data.txt", "r");

    fscanf(f, "%f", bagWeight);
    thing *thingList = (thing *)malloc(sizeof(thing));
    int i = 0;
    if (f != NULL)
    {
        while (!feof(f))
        {
            fscanf(f, "%f%f%[^\n]", &thingList[i].weight, &thingList[i].value, &thingList[i].name);
            thingList[i].valuePerWeight = thingList[i].value / thingList[i].weight;
            thingList[i].pickedNumber = 0;
            i++;
            thingList = realloc(thingList, sizeof(thing) * (i + 1));
        }
        fclose(f);
    }
    *n = i;
    return thingList;
}

void printThingList(thing *thingList, int n, float bagWeight, float originalBagWeight)
{
    int i;
    float totalWeight = 0;
    float totalValue = 0;
    printf("|STT|          Name          |   Weight   |   Value   |   ValuePerWeight   |   PickedNumber   |\n\n");
    for (i = 0; i < n; i++)
    {
        printf("|%-3d|%-24s|%12.2f|%11.2f|%20.2f|%18d|\n", i + 1, thingList[i].name, thingList[i].weight, thingList[i].value, thingList[i].valuePerWeight, thingList[i].pickedNumber);
        totalWeight += thingList[i].pickedNumber * thingList[i].weight;
        totalValue += thingList[i].pickedNumber * thingList[i].value;
    }
    printf("\nOriginalBagWeight: %f\n", originalBagWeight);
    printf("\nRemainBagWeight: %f\n", bagWeight);
    printf("\ntotalWeight: %f\n", totalWeight);
    printf("\ntotalValue: %f\n\n", totalValue);
}

void swap(thing *a, thing *b)
{
    thing temp = *a;
    *a = *b;
    *b = temp;
}

void bubleSort(thing *thingList, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (thingList[i].valuePerWeight < thingList[i + 1].valuePerWeight)
                swap(&thingList[i], &thingList[i + 1]);
        }
    }
}

void Greedy(thing *thingList, int n, float *bagWeight)
{
    int i;
    bubleSort(thingList, n);
    for (i = 0; i < n; i++)
    {
        thingList[i].pickedNumber = *bagWeight / thingList[i].weight;
        *bagWeight = *bagWeight - thingList[i].weight * thingList[i].pickedNumber;
    }
}
int main()
{
    float bagWeight;
    int n;
    thing *thingList = ReadFile(&bagWeight, &n);
    float originalBagWeight = bagWeight;
    Greedy(thingList, n, &bagWeight);
    printThingList(thingList, n, bagWeight, originalBagWeight);
    return 1;
}