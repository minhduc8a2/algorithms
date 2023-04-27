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

int findPivot(recordType *arr, int l, int r)
{
    int i = l + 1;
    keyType firstPivot = l;
    while (i <= r)
    {
        if (arr[i].key == arr[firstPivot].key)
            i++;
        else
            break;
    }
    if (i > r)
        return -1;
    if (arr[i].key > arr[firstPivot].key)
        return i;
    else
        return firstPivot;
}
int partition(recordType *arr, int l, int r, keyType pivot)
{
    while (l < r)
    {
        while (arr[l].key < pivot && l <= r)
            l++;
        while (arr[r].key >= pivot && l <= r)
            r--;
        if (l < r)
            swap(&arr[l], &arr[r]);
    }
    return l;
}

void quickSort(recordType *arr, int l, int r)
{
    keyType pivot;
    int pivotIndex = findPivot(arr, l, r);
    if (pivotIndex == -1)
        pivot = -1;
    else
        pivot = arr[pivotIndex].key;
    if (pivot != -1)
    {
        int pivotIndex = partition(arr, l, r, pivot);
        quickSort(arr, l, pivotIndex - 1);
        quickSort(arr, pivotIndex, r);
    }
}

int main()
{
    recordType *unsortedArray = (recordType *)malloc(sizeof(recordType) * 100010);
    int n;
    readFile(unsortedArray, &n);
    clock_t start = clock();
    quickSort(unsortedArray, 0, n - 1);
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