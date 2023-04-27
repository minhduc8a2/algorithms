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
void pushDown(recordType *arr, int start, int end)
{
    int current = start;
    while (current <= (end - 1) / 2)
    {
        if (current * 2 + 1 == end)
        {
            if (arr[current].key < arr[end].key)
                swap(&arr[current], &arr[end]);
            current = end;
        }
        else if (arr[current].key < arr[current * 2 + 1].key && arr[current * 2 + 1].key >= arr[current * 2 + 2].key)
        {
            swap(&arr[current], &arr[current * 2 + 1]);
            current = current * 2 + 1;
        }
        else if (arr[current].key < arr[current * 2 + 2].key && arr[current * 2 + 2].key > arr[current * 2 + 1].key)
        {
            swap(&arr[current * 2 + 2], &arr[current]);
            current = current * 2 + 2;
        }
        else
            current = end;
    }
}
void heapSort(recordType *arr, int n)
{
    int i;
    if (n <= 1)
        return;
    for (i = (n - 2) / 2; i >= 0; i--)
    {
        pushDown(arr, i, n - 1);
    }
    for (i = n - 1; i >= 2; i--)
    {
        swap(&arr[0], &arr[i]);
        pushDown(arr, 0, i - 1);
    }
    swap(&arr[0], &arr[1]);
}

int main()
{
    recordType *unsortedArray = (recordType *)malloc(sizeof(recordType) * 100010);
    int n;
    readFile(unsortedArray, &n);
    clock_t start = clock();
    heapSort(unsortedArray, n);
    clock_t end = clock();
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d%15d%30f\n", i, unsortedArray[i].key, unsortedArray[i].other);
    }
    double time = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Sort time: %f seconds\n", time);
    return 1;
}