#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <time.h>

int binomialCoefficients(int n, int k)
{

    int a, b;
    int *List = (int *)malloc((n + 1) * sizeof(int));
    List[0] = 1;
    List[1] = 1;
    int i, j;
    for (i = 2; i < n + 1; i++)
    {
        List[i] = 1;
        a = List[0];
        for (j = 1; j < i; j++)
        {
            b = List[j];
            List[j] = a + b;
            a = b;
        }
    }
    return List[k];
}

int main()
{
    printf("%d", binomialCoefficients(10, 5));
    return 1;
}