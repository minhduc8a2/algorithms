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

int sosanh(edge* a, edge *b) {
	return a->w > b->w ? 1 : 0;
}
void swap(int* a, int* b) {
	int temp = a;
	*a = *b;
	*b = temp;
}
void bublesort(Graph *G, int n) {
	int i, k;
	edge* a = &G->edges;
	for (i = 1;i < n;i++) {
		for (k = 0;k < n-1;k++) {
			if (sosanh(&a[i], &a[i + 1]) {
				swap(&(a[i]->w), &(a[i + 1]->w));
				swap(&(a[i]->u), &(a[i + 1]->u));
				swap(&(a[i]->v),&(a[i+1]->v));
			}
		}
	}
}

int main() {
	Graph G;
	freopen("dothi.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	init_Graph(&G,n);
	int i,u,v,w;
	for (i = 0;i < m;i++) {
		scanf("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	
	}
	
	return 0;
}