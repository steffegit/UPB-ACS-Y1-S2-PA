#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Declarația înainte de utilizare

typedef struct Graph {
    int V; 
    int E; 
    int **a;
}Graph;

typedef struct Node {
    int node;
    int *drum;
    int path_index;
    struct Node *next,*prev;
}Node;

typedef struct Queue {
    struct Node *front, *rear;
}Queue;

Graph* createGraph(int V, int E){
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->E = E;
    g->a = (int**)malloc(V*sizeof(int*));
    for(int i=0; i<V; i++){
        g->a[i] = (int*)malloc(V*sizeof(int));
        for(int j=0; j<V; j++){
            g->a[i][j] = 0;
        }
    }
    return g;
}

Graph *addEdge(Graph *g, int u, int v){
    g->a[u][v] = 1;
    g->a[v][u] = 1;
    return g;
}

void printGraph(Graph *g){
    for(int i=0; i<g->V; i++){
        for(int j=0; j<g->V; j++){
            printf("%d ", g->a[i][j]);
        }
        printf("\n");
    }
}

Queue *createQueue(){
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue *q, int *drum, int path_index) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    
    newNode->drum = (int *)malloc(path_index * sizeof(int));
    for (int i = 0; i < path_index; i++) {
        newNode->drum[i] = drum[i];
    }
    newNode->path_index = path_index;
    newNode->next = NULL;
    newNode->prev = q->rear;
    
    if (q->rear == NULL) { // Queue was empty
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void BFS(Graph *g, int start, int end, Queue *q) {
    int *visited = (int *)calloc(g->V, sizeof(int));
    int *distance = (int *)malloc(g->V * sizeof(int));
    int *predecesor = (int *)malloc(g->V * sizeof(int));

    for (int i = 0; i < g->V; i++) {
        distance[i] = __INT_MAX__;
        predecesor[i] = -1;
    }

    int *queue = (int *)malloc(g->V * sizeof(int));
    int front = 0, rear = 0;

    visited[start] = 1;
    distance[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < g->V; i++) {
            if (g->a[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                distance[i] = distance[current] + 1;
                predecesor[i] = current;
                queue[rear++] = i;

                if (i == end) {
                    front = rear;
                    break;
                }
            }
        }
    }

    if (distance[end] != __INT_MAX__) {
        int *path = (int *)malloc(g->V * sizeof(int));
        int path_index = 0;
        int crawl = end;

        while (crawl != -1) {
            path[path_index++] = crawl;
            crawl = predecesor[crawl];
        }

        // Reversați drumul deoarece l-am construit invers
        for (int i = 0; i < path_index / 2; i++) {
            int temp = path[i];
            path[i] = path[path_index - 1 - i];
            path[path_index - 1 - i] = temp;
        }
        
        enQueue(q, path, path_index);

        free(path);
    } else {
        printf("Nu exista drum de la %d la %d\n", start, end);
    }

    free(visited);
    free(distance);
    free(predecesor);
    free(queue);
}

void printQueue(Queue *q) {
    Node *temp = q->front;
    while(temp != NULL){
        printf("Drumul:");
        for(int i = 0; i < temp->path_index; i++){
            printf("%d ", temp->drum[i]);
        }
        printf("\n");
        temp = temp->next;
    }
}


int main(){

    Graph *g = createGraph(11, 15);
    Graph *ego1;
    Graph *ego2;
    Graph *ego3;

   int *nego = (int *)calloc(4, sizeof(int));

    addEdge(g, 0, 1);
    addEdge(g, 0, 3);
    addEdge(g, 1, 4);
    addEdge(g, 4, 7);
    addEdge(g, 7, 10);
    addEdge(g, 10, 8);
    addEdge(g, 8, 7);
    addEdge(g, 8, 9);
    addEdge(g, 9, 3);
    addEdge(g, 3, 6);
    addEdge(g, 6, 5);
    addEdge(g, 5, 4);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 9, 10);

    printf("Matricea de adiacenta a grafului:\n");
    printGraph(g);
    printf("\n");

    Queue *q = createQueue();

    for(int i=1;i<g->V;i++){
        BFS(g, 0, i, q);
    }
    printQueue(q);
    Node *temp = q->front;
    while(temp != NULL){
        nego[--temp->path_index]++;
        temp = temp->next;
    }
    for(int i=1;i<4;i++){
        printf("Numarul de noduri in egonetul de raza %d este %d\n", i, nego[i]);
    }
    ego1=createGraph(g->V,1);
    ego2=createGraph(g->V,2);
    ego3=createGraph(g->V,3);
    temp=q->front;
    while(temp!=NULL){
        int index=temp->path_index--;
        if(index==1){
            addEdge(ego1,temp->drum[0],temp->drum[1]);
        }
       else if(index==2){
            addEdge(ego2,temp->drum[0],temp->drum[1]);
            addEdge(ego2,temp->drum[1],temp->drum[2]);
        }
        else if(index==3){
            addEdge(ego3,temp->drum[0],temp->drum[1]);
            addEdge(ego3,temp->drum[1],temp->drum[2]);
            addEdge(ego3,temp->drum[2],temp->drum[3]);
        }
        temp=temp->next;
    }
    printf("Egonetul de raza 1:\n");
    printGraph(ego1);
    printf("\nEgonetul de raza 2:\n");
    printGraph(ego2);
    printf("\nEgonetul de raza 3:\n");
    printGraph(ego3);
    return 0;

}