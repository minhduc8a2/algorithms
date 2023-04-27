#include <stdio.h>
#include <malloc.h>

typedef struct {
	int person;
	int job;
	int time;

} Assignment;


int **  init( int *n) {
	int i,j;
	scanf("%d", n);
	int** matrix = (int**)malloc(sizeof(int) * *n);
	for ( i = 0; i < *n; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * *n);
	}
	for ( i = 0; i < *n; i++)
	{
		for (j = 0; j < *n; j++)
		{
			scanf("%d", &matrix[i][j]);

		}
	}
	return matrix;
}
int calculateLowerBound(int nextLevel, int** matrix, int n, int* jobSelected, int timeSum) {
	int i, j;
	int sum = 0;
	int min = _CRT_INT_MAX;
	for (i = nextLevel; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (min > matrix[i][j] && jobSelected[j] != 1) min = matrix[i][j];
		}
		sum += min;
	}
	return sum + timeSum;
}
void branchAndBoundRecursive(int ** matrix,int n,int lowerBound, int*timeSum, int person,int *jobSelected,int *bestTimeSum,Assignment*list,Assignment*finalList) {
	int i;

	if (lowerBound > *bestTimeSum) return;
	if (person == n) {
		if (*bestTimeSum > *timeSum) {
			*bestTimeSum = *timeSum;
			for ( i = 0; i < n; i++)
			{
				finalList[i].person = list[i].person;
				finalList[i].job = list[i].job;
				finalList[i].time = list[i].time;
			}
		}
		return;
	}
	for ( i = 0; i < n; i++)
	{
		if (jobSelected[i] == 1) continue;
		*timeSum += matrix[person][i];
		jobSelected[i] = 1;
		list[person].job = i;
		list[person].person = person;
		list[person].time = matrix[person][i];
		int nextLowerBound = calculateLowerBound(person+1, matrix, n, jobSelected, *timeSum);
		branchAndBoundRecursive(matrix, n, nextLowerBound, timeSum, person + 1, jobSelected, bestTimeSum,list,finalList);
		*timeSum -= matrix[person][i];
		jobSelected[i] = 0;
	}

}

void branchAndBound() {
	int n;
	int** matrix = init(&n);
	int timeSum = 0;
	int * jobSelected = (int*) malloc(sizeof(int) *n);
	int i;
	for ( i = 0; i < n; i++)
	{
		jobSelected[i] = 0;
	}
	Assignment* list = (Assignment*)malloc(sizeof(Assignment) * n);
	Assignment* finalList = (Assignment*)malloc(sizeof(Assignment) * n);
	int bestTimeSum = _CRT_INT_MAX;
	branchAndBoundRecursive(matrix,n,calculateLowerBound(0,matrix,n,jobSelected,timeSum),&timeSum,0,jobSelected,&bestTimeSum,list,finalList);
	printf("person - job - time\n");
	for ( i = 0; i < n; i++)
	{
		printf("%d - %d - %d\n",finalList[i].person+1, finalList[i].job+1, finalList[i].time);

	}

	
	printf("time sum : %d", bestTimeSum);
}

int main() {
	freopen("file.txt", "r", stdin);
	branchAndBound();
	
	return 0;
}