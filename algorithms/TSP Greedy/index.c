#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	int numberOfVertexs;
	float** matrix;

}Graph;

Graph * init_Graph() {
	int n;
	scanf("%d", &n);
	Graph *G = (Graph*) malloc(sizeof(Graph));
	G->numberOfVertexs = n;
	G->matrix = (float**)malloc(n * sizeof(float*));
	int i,k;
	for ( i = 0; i < n; i++)
	{
		G->matrix[i] = (float*)malloc(n * sizeof(float));
	}
	for ( i = 0; i < n; i++)
	{
		for (k = 0; k < n; k++)
		{
			scanf("%f", &G->matrix[i][k]);
		}
	}
	return G;
}
int root(int x, int* parent) {
	while (x != parent[x]) {
		x = parent[x];
	}
	return x;
}

int nearestNeighbour(int x, Graph * G, int * parent, int *mark) {
	float min = 999999999;
	int minVertex = -1;
	int i;
	for ( i = 0; i <G->numberOfVertexs ; i++)
	{
		if (mark[i] == 1 || G->matrix[x][i]==0) {

			continue;
		}
		int rootX = root(x, parent);
		int rootY = root(i, parent);
		if (rootX == rootY) continue;
		if (min > G->matrix[x][i]) {
			min = G->matrix[x][i];
			minVertex = i;
		}
	}
	return minVertex;
}


	

int Greedy(Graph* G, int x, int * mark, int * parent,int *path, float * sum, int start) {
	
	
	mark[x] = 1;
	int nearestNeighbourOfX = nearestNeighbour(x,G,parent,mark);
	
	if (nearestNeighbourOfX == -1) {
		if (G->matrix[x][start] != 0) {
			*sum = *sum + G->matrix[x][start];
			return x;
		}
		return 0;
	}

	int rootX = root(x, parent);
	int rootY = root(nearestNeighbourOfX, parent);
	
	
	parent[rootY] = rootX;
	path[nearestNeighbourOfX] = x;

	*sum = *sum + G->matrix[x][ nearestNeighbourOfX];
	printf("%f ", G->matrix[x][nearestNeighbourOfX]);
	return Greedy(G, nearestNeighbourOfX, mark, parent, path, sum,start);

	
}
void printMatrix(Graph* G) {
	int i, k;
	for ( i = 0; i < G->numberOfVertexs; i++)
	{
		for (k = 0; k < G->numberOfVertexs; k++)
		{
			printf("%f ", G->matrix[i][k]);
		}printf("\n");
	}
}

void printPath(int x,int *parent) {
	if (x == 0) return;
	printPath(parent[x],parent);
	printf("%d ", x);

}
int main() {
	freopen("dothi.txt", "r", stdin);
	Graph* G = init_Graph();
	int* parent = (int*)malloc(G->numberOfVertexs * sizeof(int));
	int* path = (int*)malloc(G->numberOfVertexs * sizeof(int));
	int* mark = (int*)malloc(G->numberOfVertexs * sizeof(int));
	int i;
	for (i = 0; i < G->numberOfVertexs; i++)
	{
		parent[i] = i;
		path[i] = 0;
		mark[i] = 0;
	}
	float sum = 0;
	int start = 3;
	/*printMatrix(G);*/
	int haveCircle = Greedy(G, start, mark, parent, path, &sum, start);
	
	printf("\n%f %d\n", sum, haveCircle);
	
	return 0;
}
