

#include <stdio.h>
#define MAX_LENGTH 100
#define NO_EDGE -999999
int mark[MAX_LENGTH];
int parent[MAX_LENGTH];
int distance[MAX_LENGTH];

typedef struct {
	int n, m;
	int matrix[MAX_LENGTH][MAX_LENGTH];
} Graph;

void add_edge(Graph* G, int u, int v, int p) {
	G->matrix[u][v] = p;



}
void initGraph(Graph* G) {
	int n, m, u, v, i, p, j;
	scanf("%d%d", &n, &m);
	G->n = n;
	G->m = m;
	for (i = 1;i <= G->n; i++) {
		for (j = 1;j <= G->n; j++) {
			G->matrix[i][j] = NO_EDGE;
		}
	}
	for (i = 1;i <= G->m; i++) {
		scanf("%d%d%d", &u, &v, &p);
		add_edge(G, u, v, p);

	}
}






void Bellman_Ford(Graph* G,int x) {
	
	distance[x] = 0;


}


int main()
{
	Graph G;
	freopen("dothi.txt", "r", stdin);
	initGraph(&G);
	int i,j, weightOfCircle=0,currentNode;
	

	for (i = 1;i <= G.n;i++) {
			mark[i] = 0;

	}
	

	return 0;
}
