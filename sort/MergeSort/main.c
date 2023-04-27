#include <stdio.h>
#include <malloc.h>
#include <limits.h>

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

void split(recordType *arr, int n, recordType *arr1, int n1, recordType *arr2, int n2)
{
    int i;
    for (i = 0; i < n1; i++)
    {
        assign(&arr1[i], &arr[i]);
    }
    for (i = 0; i < n2; i++)
    {
        assign(&arr2[i], &arr[i + n1]);
    }
}

void merge(recordType *arr, int n, recordType *arr1, int n1, recordType *arr2, int n2)
{
    int i, l, k;
    i = l = k = 0;
    while (l < n1 && k < n2)
    {
        if (arr1[l].key <= arr2[k].key)
            assign(&arr[i++], &arr1[l++]);
        else
            assign(&arr[i++], &arr2[k++]);
    }
    while (l < n1)
        assign(&arr[i++], &arr1[l++]);
    while (k < n2)
        assign(&arr[i++], &arr2[k++]);
}
void mergeSort(recordType *arr, int n)
{
    if (n <= 1)
        return;
    int n1 = n / 2;
    int n2 = n - n1;
    recordType *arr1 = (recordType *)malloc(n1 * sizeof(recordType));
    recordType *arr2 = (recordType *)malloc(n2 * sizeof(recordType));
    split(arr, n, arr1, n1, arr2, n2);
    mergeSort(arr1, n1);
    mergeSort(arr2, n2);
    merge(arr, n, arr1, n1, arr2, n2);
}

int main()
{
    recordType *unsortedArray = (recordType *)malloc(sizeof(recordType) * 100010);
    int n;
    readFile(unsortedArray, &n);
    mergeSort(unsortedArray, n);

    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d%15d%30f\n", i, unsortedArray[i].key, unsortedArray[i].other);
    }

    return 1;
}