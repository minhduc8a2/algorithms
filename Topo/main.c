#include <stdio.h>
typedef struct{
    int n;
    int matrix[100][100];
}Graph;

void init_Graph(Graph *G){
    int i,j;
    scanf("%d", &G->n);
    int m;
    scanf("%d",&m);
    for(i=0;i<G->n;i++){
         for(j=0;j<G->n;j++){
            G->matrix[i][j] =0;

            }
    }
    int u,v;
     for(i=0;i<m;i++){
        scanf("%d%d",&u,&v);
        G->matrix[u-1][v-1] =1;

    }

}

typedef struct{
    int front;
    int back;
    int arr[100];
}Queue;

void make_null_queue(Queue*Q){
    Q->front =0;
    Q->back=-1;
}

void enqueue(Queue*Q,int x){
    Q->arr[++Q->back] = x;
}
int frontQueue(Queue*Q){
    return Q->arr[Q->front];
}

void dequeue(Queue*Q){
    Q->front++;
}
int empty_queue(Queue*Q){
    return Q->front>Q->back;
}
typedef struct{
    int size;
    int arr[100];
}List;
void make_null_list(List*L){
    L->size =0;
}

void push_back(List*L,int x){
    L->arr[L->size++] = x;
}
int element_at(List*L,int i){
    return L->arr[i];
}

void copy_list(List*L1,List*L2){
    make_null_list(L1);
    int i;
    for(i=0;i<L2->size;i++){
        push_back(L1,element_at(L2,i));
    }
}
void topo(Graph *G, int *rank){
    int degree[100];
    int i,j;
    for(i=0;i<G->n;i++){
        degree[i]=0;
        rank[i]=-1;
        for(j=0;j<G->n;j++){
            if(G->matrix[j][i]!=0) degree[i]++;
        }
    }

    
    List L1,L2;
    make_null_list(&L1);
    for(i=0;i<G->n;i++){
        if(degree[i]==0) {
                push_back(&L1,i);

        }
    }
   int rankCount =0;

    while(L1.size>0){
       make_null_list(&L2);
        for(i=0;i<L1.size;i++){
            int u = element_at(&L1,i);
            rank[u]=rankCount;

            int v;
            for(v=0;v <G->n;v++){
                if(G->matrix[u][v]!=0){
                    degree[v]--;
                    if(degree[v]==0) {
                            push_back(&L2,v);

                    }
                }
            }
           

        }
         copy_list(&L1,&L2);
            rankCount++;
    }
}

int main(){
    freopen("dothi.txt", "r",stdin);
    Graph G;
    
    init_Graph(&G);
    int rank[100];
    topo(&G,rank);
    int i;
    for( i=0;i<G.n;i++){
        printf("%d ",rank[i]);
    }
    
    return 1;
}
