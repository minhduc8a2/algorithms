//#include <stdio.h>
//#define MAX_LENGTH 100
//#define INFINITY 999999
//
//int mark[MAX_LENGTH];
//int lengthToVertex[MAX_LENGTH];
//int parentOfVertex[MAX_LENGTH];
//
//typedef struct {
//	int n, m;
//	int edge_matrix[MAX_LENGTH][MAX_LENGTH];
//} Graph;
//
//void initGraph(Graph* G) {
//	int i,j;
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
//			printf("%d ",G->edge_matrix[i][j]);
//
//		}
//		printf("\n");
//
//	}
//}
//
//void add_edge(Graph* G,int u,int v,int w) {
//	if (u > G->n || v > G->n) {
//		printf("khong the them canh %d - %d vao do thi", u, v);
//		return;
//	}
//
//	G->edge_matrix[u][v] = w;
//	G->edge_matrix[v][u] = w;
//
//}
//
//void Dijkstra(Graph* G,int start) {
//
//	int i, j;
//	for (i = 1; i <= G->n; i++) {
//		lengthToVertex[i] = INFINITY;
//		mark[i] = 0;
//		parentOfVertex[i] = -1;
//	}
//	lengthToVertex[start] = 0;
//	parentOfVertex[start] = -1;
//
//	for (i = 1;i <= G->n;i++) {
//		int minLength = INFINITY;
//		int minVertex = start;
//		for (j = 1;j <= G->n;j++) {
//		
//			if (mark[j] == 1) continue;
//			if (minLength > lengthToVertex[j]) {
//				minLength = lengthToVertex[j];
//				minVertex = j;
//			}
//		}
//
//		mark[minVertex] = 1;
//		int newLength;
//		for (j = 1;j <= G->n;j++) {
//			if (G->edge_matrix[minVertex][j] == INFINITY || mark[j] == 1) continue;
//			newLength = G->edge_matrix[minVertex][j] + lengthToVertex[minVertex];
//			if (newLength < lengthToVertex[j]) {
//				lengthToVertex[j] = newLength;
//				parentOfVertex[j] = minVertex;
//			}
//		}
//	}
//
//
//
//
//	
//
//}
//
//int main() {
//	Graph G;
//	int  i, u, v;
//	int w;
//	freopen("dothi.txt", "r", stdin);
//	scanf("%d%d", &G.n, &G.m);
//	
//	printf("%d %d", G.n, G.m);
//	initGraph(&G);
//
//	for (i = 0;i < G.m;i++) {
//		scanf("%d%d%d", &u, &v,&w);
//		add_edge(&G, u, v, w);
//
//	}
//	
//
//	//printGraph(&G);
//	Dijkstra(&G, 1);
//	for (i = 1;i <= G.n;i++) {
//		printf("chieu dai tu dinh 1 den dinh %d la: %d   \n",i,lengthToVertex[i]);
//	}
//
//
//
//
//	return 1;
//}