//#include <stdio.h>
//#define MAX_LENGTH 100
//#define INFINITY 999999
//
//typedef struct {
//	int size;
//	int data[MAX_LENGTH];
//}List;
//void makeList(List *L) {
//	L->size = 0;
//
//}
//void push_list(List *L, int x) {
//	L->data[L->size] = x;
//
//	L->size++;
//}
//typedef struct {
//	int data[MAX_LENGTH];
//	int size;
//} Stack;
//void make_null_stack(Stack* S) {
//	S->size = 0;
//}
//void push(Stack* S, int x) {
//	S->data[S->size] = x;
//	S->size++;
//}
//int top(Stack* S) {
//	return S->data[S->size - 1];
//}
//void pop(Stack* S) {
//	S->size--;
//}
//int empty(Stack* S) {
//	return S->size == 0;
//}
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
//
//}
//
//
//int num[MAX_LENGTH];
//int min_num[MAX_LENGTH];
//Stack S;
//List L;
//int k = 1;
//void initNumAndMinNum(int n) {
//	int i;
//	for (i = 1;i <= n;i++) {
//		num[i] = -1;
//		min_num[i] = -1;
//	}
//}
//
//
//
//void strong_connect(Graph* G, int x) {
//	num[x] = min_num[x] = k;
//	k++;
//	push(&S, x);
//
//
//}
//
//
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
//	makeList(&L);
//	make_null_stack(&S);
//	strong_connect(&G, 1);
//
//
//
//
//
//	return 1;
//}