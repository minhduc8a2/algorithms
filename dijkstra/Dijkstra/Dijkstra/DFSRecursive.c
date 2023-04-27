//#include <stdio.h>
//#define MAX_LENGTH 100
//#define INFINITY 999999
//
//
//
//typedef struct {
//	int n, m;
//	int edge_matrix[MAX_LENGTH][MAX_LENGTH];
//} Graph;
//
//void initGraph(Graph* G) {
//	int i, j;
//	for (i = 1;i <= G->n;i++) {
//		for (j = 1;j <= G->n;j++) {
//			G->edge_matrix[i][j] = INFINITY;
//
//		}
//
//	}
//}
//
//void printGraph(Graph* G) {
//	int i, j;
//	for (i = 1;i <= G->n;i++) {
//		for (j = 1;j <= G->n;j++) {
//			printf("%d ", G->edge_matrix[i][j]);
//
//		}
//		printf("\n");
//
//	}
//}
//
//void add_edge(Graph* G, int u, int v) {
//	if (u > G->n || v > G->n) {
//		printf("khong the them canh %d - %d vao do thi", u, v);
//		return;
//	}
//
//	G->edge_matrix[u][v] = 1;
//	G->edge_matrix[v][u] = 1;
//
//}
//
//int mark[MAX_LENGTH];
//int i;
//void initMark() {
//	for (i = 0;i < MAX_LENGTH;i++) {
//		mark[i] = 0;
//	}
//}
//
//void DFS_Recursive(Graph* G, int startNode) {
//	mark[startNode]=1;
//	printf("%d ", startNode);
//	int i;
//	for (i = 1;i <= G->n;i++) {
//		if (G->edge_matrix[startNode][i] != INFINITY && mark[i]!=1) {
//			DFS_Recursive(G, i);
//		}
//	}
//}
//
//
//
//int main() {
//	Graph G;
//	int  i, u, v;
//	int w;
//	freopen("dothi.txt", "r", stdin);
//	scanf("%d%d", &G.n, &G.m);
//
//	
//	initGraph(&G);
//
//	for (i = 0;i < G.m;i++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//
//	}
//
//
//	initMark();
//	DFS_Recursive(&G, 1);
//
//
//
//
//	return 1;
//}