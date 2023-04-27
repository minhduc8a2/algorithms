#include <stdio.h>
#include<limits.h>
#include <malloc.h>
typedef struct {
	int** matrix;
	int n;
}Graph;

void initGraph(Graph* G, int n) {
	G->n = n;
	G->matrix = (int**)malloc(sizeof(int*) * n);
	int i,j;
	for ( i = 0; i < n; i++)
	{
		G->matrix[i] = (int*)malloc(sizeof(int) * n);
		for (j = 0; j < n; j++)
		{
			
			G->matrix[i][j] = 0;
		}
	}
	

}
void addEdge(Graph* G, int u, int v, int w) {
	G->matrix[u][v] = w;
	G->matrix[v][u] = w;
}
void prim(Graph* G,int s, Graph*T, int *sum) {
	int* parent = (int*)malloc(sizeof(int) * G->n);
	int* distance = (int*)malloc(sizeof(int) * G->n);
	int* mark = (int*)malloc(sizeof(int) * G->n);
	int i,j;
	for ( i = 0; i < G->n; i++)
	{
		parent[i] = -1;
		distance[i] = INT_MAX;
		mark[i] = 0;
	}
	distance[s] = 0;
	parent[s] = s;
	
	for ( i = 0; i < G->n; i++)
	{
		int minDistance = INT_MAX;
		int minVertex ;
		for ( j = 0; j < G->n; j++)
		{
			if ( distance[j] < minDistance && mark[j]==0) {
				minDistance = distance[j];
				minVertex = j;
			}
		}
		*sum += distance[minVertex];
		mark[minVertex] = 1;
		for ( j = 0; j < G->n; j++)
		{
			if (mark[j] == 0 && G->matrix[minVertex][j]!=0) {
				if (distance[j] > G->matrix[minVertex][j])
				{
					parent[j] = minVertex;

					distance[j] = G->matrix[minVertex][j];
				}
			}
		}
	}
	for ( i = 0; i < G->n; i++)
	{
		addEdge(T, parent[i], i, G->matrix[parent[i]][i]);
	}
	

}
void printGraph(Graph* G) {
	int i,j;
	for ( i = 0; i < G->n; i++)
	{
		for ( j = i; j < G->n; j++)
		{
			if (G->matrix[i][j] != 0)
			printf("%d %d %d\n", i+1, j+1, G->matrix[i][j]);

		}
	}
}
int main() {
	freopen("file.txt", "r", stdin);
	Graph G;
	Graph T;
	int sum = 0;
	int n, m;
	int x, y, w;
	scanf("%d%d", &n, &m);

	
	initGraph(&G, n);
	initGraph(&T,n);
	int j;
	for (j = 0; j < m; j++)
	{
		scanf("%d%d%d", &x, &y, &w);
		addEdge(&G, x - 1, y - 1, w);
	}
	//printGraph(&G);

	prim(&G, 0, &T,&sum);
	printf("%d\n", sum);

	printGraph(&T);
	return 0;
}