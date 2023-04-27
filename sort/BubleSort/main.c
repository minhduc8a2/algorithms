#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

typedef int keyType;
typedef float otherType;

typedef struct
{
    keyType key;
    otherType other;
} recordType;

void assign(recordType *a, recordType *b)
{
    a->key = b->key;
    a->other = b->other;
}
void swap(recordType *a, recordType *b)
{
    recordType temp;
    assign(&temp, a);
    assign(a, b);
    assign(b, &temp);
}

void readFile(recordType *arr, int *n)
{
    FILE *f = fopen("data.txt", "r");
    int i = 0;
    if (f != NULL)
        while (!feof(f))
        {
            fscanf(f, "%d%f", &arr[i].key, &arr[i].other);
            i++;
        }
    fclose(f);
    *n = i - 1;
}

void bubleSort(recordType *arr, int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].key > arr[j + 1].key)
                swap(&arr[j], &arr[j + 1]);
        }
    }
}
int main()
{
    recordType *unsortedArray = (recordType *)malloc(sizeof(recordType) * 100010);
    int n;
    readFile(unsortedArray, &n);
    clock_t start = clock();
    bubleSort(unsortedArray, n);
    clock_t end = clock();
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d%15d%30f\n", i, unsortedArray[i].key, unsortedArray[i].other);
    }
    double time = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Time for sorting: %f\n", time);

    return 1;
}