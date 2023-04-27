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

int sosanh(edge* a, edge* b) {
	return a->w > b->w ? 1 : 0;
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void bublesort(Graph* G, int n) {
	int i, k;
	
	for (i = 1;i < n;i++) {
		for (k = 0;k < n-1;k++) {
			if (sosanh(&G->edges[k], &G->edges[k + 1])) {
				swap(&G->edges[k].w, &G->edges[k + 1].w);
				swap(&G->edges[k].v, &G->edges[k + 1].v);
				swap(&G->edges[k].u, &G->edges[k + 1].u);
					
			}
		}
	}
}

int root(int x) {
	
	while (x != parent[x]) {
		x = parent[x];
	}

	return x;
}

void kruskal(Graph* G, Graph *T) {
	bublesort(G, G->m);
	int i;
	for ( i = 1; i <= G->n; i++)
	{	
		parent[i] = i;
	}

	int sum = 0;
	int u, v, w, rootU, rootV;
	for ( i = 0; i < G->m; i++)
	{
		u = G->edges[i].u;
		v = G->edges[i].v;
		w = G->edges[i].w;
		rootU = root(u);
		rootV = root(v);
		if (rootU != rootV) {
			add_edge(T, u, v, w);
			if (rootV != v) parent[u] = v;
			else parent[v] = u;
			sum += w;
		}

	}
}



int main() {
	Graph G,T;
		freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G, n);
	init_Graph(&T, n);
	int i, u, v, w;
	for (i = 0;i < m;i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);

	}
	kruskal(&G, &T);
	
	return 0;
}