#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF 1000000
#define dim 9

typedef struct {
    int data[100];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    if (q->front == q->rear) return 1;
    else return 0;
}

void enqueue(Queue *q, int x) {
    q->data[q->rear++] = x;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

void BFS(int n, int adj[][dim], int s, char vertexNames[]) {
    int color[dim], d[dim], parent[dim];
    int discoveryOrder[dim];
    int orderIdx = 0;
    
    for (int u = 0; u < n; u++) {
        color[u] = WHITE;
        d[u] = INF;
        parent[u] = -1;
    }
    
    color[s] = GRAY;
    d[s] = 0;
    parent[s] = -1;
    
    Queue q;
    initQueue(&q);
    enqueue(&q, s);
    
    while (!isEmpty(&q)) {
        int u = dequeue(&q);
        discoveryOrder[orderIdx++] = u;
        
        for (int v = 0; v < n; v++) {
            if (adj[u][v] == 1 && color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                parent[v] = u;
                enqueue(&q, v);
            }
        }
        color[u] = BLACK;
    }
    
    printf("Vertices in the order of their discovery:\n");
    for (int i = 0; i < n; i++) {
        printf("%c", vertexNames[discoveryOrder[i]]);
    }
    printf("\n\n");
    
    printf("%-10s %-25s %-15s\n", "Vertex", "Shortest-path Distance", "Predecessor (Parent)");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-10c", vertexNames[i]);
        if (d[i] == INF) {
            printf("%-25s", "INF");
        } else {
            printf("%-25d", d[i]);
        }
        if (parent[i] == -1) {
            printf("%-15s\n", "NIL (Source)");
        } else {
            printf("%-15c\n", vertexNames[parent[i]]);
        }
    }
}

int main() {
    char vertexNames[dim] = {'S', 'R', 'U', 'V', 'T', 'W', 'Y', 'X', 'Z'};
    int adjMatrix[dim][dim] = {
        // S  R  U  V  T  W  Y  X  Z
        {  0, 1, 1, 1, 0, 0, 0, 0, 0 }, // S (0)[cite: 28]
        {  1, 0, 0, 0, 1, 1, 0, 0, 0 }, // R (1)[cite: 28]
        {  1, 0, 0, 0, 1, 0, 1, 0, 0 }, // U (2)[cite: 28]
        {  1, 0, 0, 0, 0, 1, 0, 1, 0 }, // V (3)[cite: 28]
        {  0, 1, 1, 0, 0, 0, 0, 0, 1 }, // T (4)[cite: 28]
        {  0, 1, 0, 1, 0, 0, 0, 0, 1 }, // W (5)[cite: 28]
        {  0, 0, 1, 0, 0, 0, 0, 0, 1 }, // Y (6)[cite: 28]
        {  0, 0, 0, 1, 0, 0, 0, 0, 1 }, // X (7)[cite: 28]
        {  0, 0, 0, 0, 1, 1, 1, 1, 0 }  // Z (8)[cite: 28]
    };
    
    BFS(dim, adjMatrix, 0, vertexNames);
    return 0;
}
