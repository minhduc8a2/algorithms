

#include <stdio.h>
#define MAX_LENGTH 100
int mark[MAX_LENGTH];
int count = 0;
typedef struct {
	int n, m;
	int matrix[MAX_LENGTH][MAX_LENGTH];
} Graph;

void add_edge(Graph* G, int u, int v, int p) {
	G->matrix[u][v] = p;
	G->matrix[v][u] = p;



}
void initGraph(Graph* G) {
	int n, m, u, v, i, p, j;
	scanf("%d%d", &n, &m);
	G->n = n;
	G->m = m;
	for (i = 1;i <= G->n; i++) {
		for (j = 1;j <= G->n; j++) {
			G->matrix[i][j] = -1;
		}
	}
	for (i = 1;i <= G->m; i++) {
		scanf("%d%d%d", &u, &v, &p);
		add_edge(G, u, v, p);

	}
}
typedef struct {
	int size;
	int list[MAX_LENGTH];

}Stack;

void initStack(Stack* S) {
	S->size = 0;
}

void pushStack(Stack* S, int x) {
	S->list[S->size] = x;
	S->size++;
}
int topStack(Stack* S) {
	return S->list[S->size - 1];
}
int popStack(Stack* S) {
	if (S->size == 0) return -1;

	S->size--;
	return S->list[S->size];


}
int isEmptyStack(Stack* S) {
	return S->size == 0;
}

typedef struct {
	int size;
	int data[MAX_LENGTH];
}List;
void initList(List* L) {
	L->size = 0;
}
void addList(List* L, int x) {
	L->data[L->size++] = x;
}
int elementAt(List* L, int i) {
	return L->data[i];
}
void removeList(List* L, int x) {
	L->data[L->size++] = x;
}

List neighbours(Graph* G, int x) {
	List L; int i;
	initList(&L);
	for (i = 1;i <= G->n;i++) {
		if (x == i) continue;
		if (G->matrix[x][i] != -1) addList(&L, i);
	}
	return L;
}


void DFS(Graph* G, int x) {
	if (mark[x] == 1) return;
	printf("%d ", x);
	mark[x] = 1;
	count++;
	List L = neighbours(G, x);
	int i, neighbour;
	for (i = 0;i < L.size;i++) {
		neighbour = elementAt(&L, i);
		if (mark[neighbour] == 1) continue;
		DFS(G, neighbour);
	}
}


int distance[MAX_LENGTH];
int parent[MAX_LENGTH];
List neighboursOfX;
int L[MAX_LENGTH];
int isEmptyList(Graph* G) {
	int i;

	for (i = 1;i <= G->n;i++) {
		if (L[i] == 1) {
			return 0;
		}
	}
	return 1;
}
void Dijkstra(Graph* G, int x) {
	L[x] = 1;
	distance[x] = 0;
	parent[x] = 0;

	int i, item, newDistance, minNode = 1, minNodeValue = 999999, neighbour;
	while (!isEmptyList(G)) {
		//lay phan tu co distance lon nhat
		minNode = 1; minNodeValue = 999999;
		for (item = 1;item <= G->n;item++) {
			if (L[item] == 0) continue;
			if (distance[item] < minNodeValue) {
				minNodeValue = distance[item];
				minNode = item;
			}

		}
		mark[minNode] = 1;
		neighboursOfX = neighbours(G, minNode);
		L[minNode] = 0;
		for (i = 0;i < neighboursOfX.size;i++) {
			neighbour = elementAt(&neighboursOfX, i);
			if (mark[neighbour] == 1) continue;
			newDistance = G->matrix[minNode][neighbour] + distance[minNode];
			if (distance[neighbour] > newDistance) {
				parent[neighbour] = minNode;
				distance[neighbour] = newDistance;
			}
			L[neighbour] = 1;
		}


	}

}


int main()
{
	Graph G;
	freopen("dothi.txt", "r", stdin);
	initGraph(&G);
	
	int i;
	for (i = 1;i <= G.n;i++) {
		distance[i] = 999999;
		parent[i] = 0;
		L[i] = 0;

	}

	initList(&neighboursOfX);
	Dijkstra(&G, 1);
	int ok = 1;
	for (i = 1;i <= G.n;i++) {
		if (distance[i] == 999999) {
			ok = 0;
			
		}
		

	}
	if (ok) printf("OK");
	else printf("NOT OK");

	return 0;
}
