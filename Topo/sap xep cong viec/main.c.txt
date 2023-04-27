#include <stdio.h>
#include <malloc.h>
#include <limits.h>

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


void getDataFromFile(Graph*G,int *timeCost){
    int i;
    int cost,v;
    for(i=0;i<G->n-2;i++){
       
        scanf("%d",&cost);
        timeCost[i]=cost;
        do{
            scanf("%d",&v);
            if(v==0) break;
            add_edge_directedGraph(G,v-1,i,1);
        }
        while(v!=0);
       
    }
}
int* getArrayInDegree(Graph* G){
    int *degree = (int*)malloc(sizeof(int)*G->n);
    int i,j;
    for(i=0;i<G->n;i++){
        degree[i] = 0;
        for(j=0;j<G->n;j++){
           if(G->matrix[j][i]) degree[i]++;
        }
    }
    return degree;
}
int* getArrayOutDegree(Graph* G){
    int *degree = (int*)malloc(sizeof(int)*G->n);
    int i,j;
    for(i=0;i<G->n;i++){
        degree[i] = 0;
        for(j=0;j<G->n;j++){
           if(G->matrix[i][j]) degree[i]++;
        }
    }
    return degree;
}

void copyQueue(Queue * list1, Queue * list2){
    init_queue(list1);
    while(!empty_queue(list2)){
        int u = pop_queue(list2);
        push_queue(list1,u);

    }
}

int max (int a, int b){
    return a > b ? a : b;
}
int min (int a, int b){
    return a < b ? a : b;
}

void jobManage(){
    int n;
    Graph*G = (Graph*)malloc(sizeof(Graph));
    
    scanf("%d",&n);
    init_graph(G,n+2);
    int *timeCost = (int*)malloc(sizeof(int)*G->n);
    getDataFromFile(G,timeCost);
    int checkVertex,  checkTime;
    scanf("%d%d",&checkVertex,&checkTime);
    checkVertex--;
    int alpha = G->n-2;
    int beta = G->n-1;
    timeCost[alpha] = 0;
    timeCost[beta] = 0;
    int *degreeInArray = getArrayInDegree(G);
    int * degreeOutArray = getArrayOutDegree(G);
    int i,j;
    for(i=0;i<G->n-2;i++){
        if(degreeInArray[i]==0){
            add_edge_directedGraph(G,alpha,i,1);
        }
    }
    for(i=0;i<G->n-2;i++){
        if(degreeOutArray[i]==0){
            add_edge_directedGraph(G,i,beta,1);
        }
    }
    degreeInArray = getArrayInDegree(G);
    //topo
    Queue* list1 = (Queue*) malloc(sizeof(Queue));
    Queue* list2 = (Queue*) malloc(sizeof(Queue));
    Queue* vertexRankIncreasing = (Queue*) malloc(sizeof(Queue));
    init_queue(list1);
    init_queue(vertexRankIncreasing);
    int *rank = (int*)malloc(sizeof(int)*G->n);
    int rankIncrement = 0;
    for ( i = 0; i < G->n; i++)
    {
        rank[i]=-1;
    }
    for ( i = 0; i < G->n; i++)
    {
        if(degreeInArray[i]==0) push_queue(list1,i);
    }

    while(!empty_queue(list1)){
        init_queue(list2);
        while(!empty_queue(list1)){
            int u = pop_queue(list1);
            for ( i = 0; i < G->n; i++)
            {
                if(G->matrix[u][i]!=0 && rank[i]==-1){
                    degreeInArray[i]--;
                    if(degreeInArray[i]==0) push_queue(list2,i);
                    
                }
            }
            rank[u] = rankIncrement;
            push_queue(vertexRankIncreasing,u);
            
        }
        copyQueue(list1,list2);
        rankIncrement++;

    }
    
    
    int *earliestTime = (int*)malloc(sizeof(int)*G->n);
    earliestTime[alpha]=0;
    for ( i = 1; i < G->n; i++)
    {
        int u = vertexRankIncreasing->matrix[i];
        earliestTime[u] = INT_MIN;
        for(j=0;j<G->n;j++){
            if(G->matrix[j][u]!=0){
                earliestTime[u] = max(earliestTime[u],earliestTime[j]+timeCost[j]);
            }
        }
    }
    int *latestTime = (int*)malloc(sizeof(int)*G->n);
    latestTime[beta]=earliestTime[beta];
    for ( i = G->n-2; i >=0; i--)
    {
        int u = vertexRankIncreasing->matrix[i];
        latestTime[u] = INT_MAX;
        for(j=0;j<G->n;j++){
            if(G->matrix[u][j]!=0){
                latestTime[u] = min(latestTime[u],latestTime[j]-timeCost[u]);
            }
        }
    }
    if(earliestTime[checkVertex]<=checkTime && checkTime<=latestTime[checkVertex]){
        printf("YES");
    }
    else printf("NO");

}

  
int main(){
    jobManage();
    
    return 1;
}