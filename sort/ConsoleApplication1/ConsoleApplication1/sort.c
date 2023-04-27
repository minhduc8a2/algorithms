#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define MAX_LENGTH 10000000
int unsortedArray[MAX_LENGTH];
void initUnsortedArray() {
	int i;
	for (i = 0;i < MAX_LENGTH;i++) {
		unsortedArray[i] = rand()%MAX_LENGTH +1;
	}
}

void swap(int * unsortedArray,int a, int b) {
	int temp = unsortedArray[a];
	unsortedArray[a] = unsortedArray[b];
	unsortedArray[b] = temp;
}
void swapV2(int *a, int* b) {
	int temp = *a;
	*a = *b;
	*b= temp;
}
void selectionSort() {
	int i,j;
	int minValue, minIndex;
	for (i = 0;i < MAX_LENGTH-1;i++) {
		minValue = unsortedArray[i];
		minIndex = i;
		for (j = i+1;j < MAX_LENGTH ;j++) {
			if (unsortedArray[j] < minValue) {
				minValue = unsortedArray[j];
				minIndex = j;
			}
		}
		swap(&unsortedArray,i, minIndex);
	}
}
void bubleSort() {
	int i, j;
	
	for (i = 0;i < MAX_LENGTH - 1;i++) {
		
		for (j = 0;j < MAX_LENGTH-1-i;j++) {
			if (unsortedArray[j] > unsortedArray[j + 1]) swap(unsortedArray, j, j + 1);
		}
		
	}
}

void insertionSort() {
	int i, j,key;

	for (i = 1;i < MAX_LENGTH;i++) {
		j = i;
		key = unsortedArray[i];
		while (unsortedArray[j - 1] >key && j>0) {
			unsortedArray[j] = unsortedArray[j - 1];
			j --;
		}
		unsortedArray[j] = key;

	}
}
void merge( int l,int m, int r) {
	int L[MAX_LENGTH], R[MAX_LENGTH];
	int i, j, k;
	int n1=m-l+1, n2=r-m;
	//copy from unsortedArray to L
	for (i = 0;i <n1;i++) {
		L[i] = unsortedArray[i + l];
	}
	for (i = 0;i < n2;i++) {
		R[i] = unsortedArray[i + m+1];
	}
	i = j = 0; k =l ;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			unsortedArray[k++] = L[i++] ;
			
		}
		else {
			unsortedArray[k++] = R[j++];
			
		}
		
	}
	for (;i < n1;i++) {
		L[i] = unsortedArray[k++];
	}
	for (;j < n2;j++) {
		R[j] = unsortedArray[k++];
	}
}

void mergeSort(int l, int r) {
	if (l < r) {
		int m = (r - l) / 2 + l;
		mergeSort(l, m);
		mergeSort(m + 1, r);
		merge(l, m, r);
	}
}
int partition(int low, int high) {
	int pivot = unsortedArray[high];
	int i = low;
	int j = low;
	for (;j < high;j++) {
		if (unsortedArray[j] < pivot) {
			swap(unsortedArray, i++, j);
		}
	}
	swap(unsortedArray, i, high);
	return i;
}
void quickSort(int low, int high) {
	if (low >= high) return;
	int p = partition(low, high);
	quickSort(low, p-1);
	quickSort(p + 1, high);
}
void heapify(int a[], int N, int root) {
	int i;
	//build max heap

	int largest = root;
	int leftNode = root * 2 + 1;
	int rightNode = root * 2 + 2;
	if ( leftNode<N && a[leftNode] > a[largest]  ) {
		largest = leftNode;
	}

	if ( rightNode < N &&  a[rightNode] > a[largest] ) {
		largest = rightNode;
	}
	
	if (largest != root) {
		swapV2(&a[largest], &a[root]);
		heapify(a, N, largest);

	}
}
void heapSort(int a[],int N) {
	int i;
	
	for (i = N / 2 - 1;i >= 0;i--) {
		heapify(a, N, i);
	}

	for (i = N - 1;i >= 0;i--) {
		swapV2(&a[0], &a[i]);
		heapify(a, i, 0);

	}
}
int main() {
	
	initUnsortedArray(&unsortedArray);
	

	clock_t tic = clock();
	heapSort(unsortedArray,MAX_LENGTH);
	clock_t toc = clock();

	printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

}