#include <stdio.h>
#include <malloc.h>

typedef struct {
    int **matrix;
    int n;
} Graph;

void init_graph(Graph*G,int n){
    G->n = n;
    G->matrix = (int **)malloc(G->n * sizeof(int*));
    int i,j;
    for(i=0;i<G->n;i++){
        G->matrix[i] = (int *)malloc(G->n * sizeof(int));
        for(j=0;j<G->n;j++){
            G->matrix[i][j] =0;
        }
    }
}

void add_edge_notdirectedGraph(Graph*G,int u, int v, int w ){
    G->matrix[u][v] = w;
    G->matrix[v][u] = w;
}

void add_edge_directedGraph(Graph*G,int u, int v, int w ){
    G->matrix[u][v] = w;
   
}

typedef struct {
    int matrix[100];
    int front, rear;
} Queue;

void init_queue(Queue* queue){
    queue->front = 0;
    queue->rear = -1;
}
void push_queue(Queue* queue,int x){
    queue->matrix[++queue->rear] = x;

}
int pop_queue(Queue* queue){
    if(queue->front > queue->rear) return -1;
    int x = queue->matrix[queue->front++];
    return x;

}

void getDataFromFile(Graph*G, int m){
    int i;
    int u,v;
    for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        add_edge_directedGraph(G,u-1,v-1,1);
    }
}
int empty_queue(Queue* queue){
    return queue->front>queue->rear;
}

void DFS(Graph*G, int * color, int u, int * haveCircle){
    int WHITE = -1;
    int GREY = 0;
    int BLACK = 1;
    if(*haveCircle) return;
    color[u] = GREY;
    int i;
    for(i=0;i<G->n;i++){
       
        if(G->matrix[u][i]!=0){

            if(color[i]==WHITE) DFS(G,color,i, haveCircle);
            else if(color[i]==GREY) {
                *haveCircle=1;
                return;
            }

        }
       
    }
    color[u] = BLACK;
    
}
int colorGraph(Graph *G,int x){
    int *color = (int*)malloc(sizeof(int)*G->n);
    int WHITE = -1;
    
    int i;
    for(i=0;i<G->n;i++){
        color[i] = WHITE;
    }
    int haveCircle = 0;
    DFS(G,color,x,&haveCircle);
    return haveCircle;


}

int main(){
    int n,m;
    Graph*G = (Graph*)malloc(sizeof(Graph));
    freopen("dothi.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(G,n);
    getDataFromFile(G,m);
    if(colorGraph(G,1)) printf("KHONG HOP LE");
    else printf("HOP LE");
    return 1;
}