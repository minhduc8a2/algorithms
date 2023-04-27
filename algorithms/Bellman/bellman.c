#include <stdio.h>

#define MAX_LENGTH 100
#define VO_CUNG 999999
int parent[MAX_LENGTH];
int distance[MAX_LENGTH];

typedef struct {
	int u, v, w;

}edge;

typedef struct {
	int n, m;
	edge edges[MAX_LENGTH];
}
Graph;


void init_Graph(Graph* G, int n) {
	G->n = n;
	G->m = 0;
}

void add_edge(Graph* G, int u, int v, int w) {

	G->edges[G->m].u = u;
	G->edges[G->m].v = v;
	G->edges[G->m++].w = w;
}
int  bellman(Graph* G, int start) {

	int i, k, u, v, w;
	for (i = 1;i <= G->n;i++) {
		parent[i] = -1;
		distance[i] = VO_CUNG;

	}

	distance[start] = 0;
	for (i = 1;i < G->n;i++) {
		for (k = 0;k < G->m;k++) {

			u = G->edges[k].u;
			v = G->edges[k].v;
			w = G->edges[k].w;
			if (distance[u] == VO_CUNG) continue;
			if (distance[u] + w < distance[v]) {
				distance[v] = distance[u] + w;
				parent[v] = u;
			}

		}
	}

	for (k = 0; k < G->m; k++) {
		int u = G->edges[k].u;
		int v = G->edges[k].v;
		int w = G->edges[k].w;
		if (distance[u] + w < distance[v]) {
			return 0;
			break;
		}
	}
	return 1;
}

void printPath(int n) {
	if (n == -1) return;
	printPath(parent[n]);
	printf("%d ", n);
}
int main() {
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	int i, u, v, w;
	for (i = 0;i < m;i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);

	}
	int notNegative = bellman(&G, 1);
	int current;
	if (notNegative)
		for (i = 1;i <= n;i++) {
			printf("path: ");
			printPath(i);
			printf("\nkhoang cach la: %d\n", distance[i]);

		}
	else printf("NO");
	return 0;
}