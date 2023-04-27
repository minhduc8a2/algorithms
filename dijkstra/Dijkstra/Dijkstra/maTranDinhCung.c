#include "stdio.h"

#define MAX_N 100
#define MAX_M 500

typedef struct {
	int x, y;
} Edge;
typedef struct {
	int n, m;
	Edge edges[MAX_M];
} Graph;



int main() {
	Graph G;
	int i, u, v;
	freopen("dothi.txt", "r", stdin);
	scanf("%d%d", &G.n, &G.m);
	for (i = 1;i <= G.m;i++) {
		scanf("%d%d", &u, &v);
		themCung(&G, i, u, v);
	}
	int maxVertex=0, maxDeg=0;
	for (i = 1;i <= G.n;i++) {
		int d = deg(&G, i);
		if (maxDeg < d) {
			maxDeg = d;
			maxVertex = i;
		}

	}
	printf("%d %d", maxVertex, maxDeg);


	return 1;

}