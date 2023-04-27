#include <stdio.h>
#include <malloc.h>
#include<limits.h>

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
int empty_queue(Queue* queue){
    return queue->front>queue->rear;
}
void getDataFromFile(Graph*G,int m){
    int i;
    int u,v,x,y;
    for(i=0;i<m;i++){
       scanf("%d%d%d%d",&u,&v,&x,&y);
       add_edge_notdirectedGraph(G,u-1,v-1,x*y);
    }
}

int notFullTree(int *mark,int n){
    int i;
    for(i=0;i<n;i++){
        if(mark[i]==0) return 1;
    }
    return 0;
}

int prim(Graph*G,int x){
    int cost = 0;
    int *parent = (int*)malloc(sizeof(int)*G->n);
    int *mark = (int*)malloc(sizeof(int)*G->n);
    int *list = (int*)malloc(sizeof(int)*G->n);
    int i=0,j;
    for(int i=0;i<G->n;i++){
        parent[i] = -1;
        mark[i] =0;
        list[i] =0;

    }
    mark[x] =1;
    list[x] =1;
  
   while(notFullTree(mark,G->n) ){
        int min = INT_MAX;
        int v = -1;
        for(i=0;i<G->n;i++){
            if(list[i]!=0){
                for(j=0;j<G->n;j++){
                    if(G->matrix[i][j]!=0 && !list[j]){
                        if(min>G->matrix[i][j]){
                            min=G->matrix[i][j];
                            v = j;
                            parent[j]=i;
                        }
                    }
                }
            }
        }
        if(v==-1) return -1;
        mark[v] = 1;
        list[v]=1;
        cost+=min;
       
   }
   
   return cost;

}



int main(){
    int n,m;
    Graph*G = (Graph*)malloc(sizeof(Graph));
    freopen("dothi.txt", "r",stdin);
    scanf("%d%d",&n,&m);
    init_graph(G,n);
    getDataFromFile(G,m);
    int result = prim(G,0);
    if(result!=-1) printf("%d",result);
   else printf("KHONG CO LOI GIAI");
    return 1;
}