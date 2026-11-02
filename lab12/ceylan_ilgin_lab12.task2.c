#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int vertex;
    int key;
} HeapNode;

typedef struct {
    int size;
    HeapNode* array[MAX];
    int pos[MAX];
} MinHeap;

HeapNode* newHeapNode(int v, int key) {
    HeapNode* node = (HeapNode*)malloc(sizeof(HeapNode));
    node->vertex = v;
    node->key = key;
    return node;
}

void swap(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;
    
    if (left <= heap->size && heap->array[left]->key < heap->array[smallest]->key)
        smallest = left;
    if (right <= heap->size && heap->array[right]->key < heap->array[smallest]->key)
        smallest = right;
        
    if (smallest != i) {
        HeapNode* smallestNode = heap->array[smallest];
        HeapNode* currentNode = heap->array[i];
        
        heap->pos[smallestNode->vertex] = i;
        heap->pos[currentNode->vertex] = smallest;
        
        swap(&heap->array[smallest], &heap->array[i]);
        minHeapify(heap, smallest);
    }
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

HeapNode* extractMin(MinHeap* heap) {
    if (heap->size == 0)
        return NULL;
        
    HeapNode* root = heap->array[1];
    HeapNode* last = heap->array[heap->size];
    
    heap->array[1] = last;
    heap->pos[root->vertex] = heap->size;
    heap->pos[last->vertex] = 1;
    
    heap->size--;
    minHeapify(heap, 1);
    
    return root;
}

void decreaseKey(MinHeap* heap, int v, int key) {
    int i = heap->pos[v];
    heap->array[i]->key = key;
    
    while (i > 1 && heap->array[i]->key < heap->array[i / 2]->key) {
        heap->pos[heap->array[i]->vertex] = i / 2;
        heap->pos[heap->array[i / 2]->vertex] = i;
        swap(&heap->array[i], &heap->array[i / 2]);
        i /= 2;
    }
}

int inHeap(MinHeap* heap, int v) {
    return heap->pos[v] <= heap->size;
}

void printHeap(MinHeap* heap) {
    printf("Current Min-Heap: [ ");
    for (int i = 1; i <= heap->size; i++) {
        printf("(Node:%d, Key:%d) ", heap->array[i]->vertex, heap->array[i]->key);
    }
    printf("]\n");
}

void primMST(int graph[MAX][MAX], int V) {
    int parent[MAX];
    int key[MAX];
    
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = V;
    
    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = INT_MAX;
        heap->array[v + 1] = newHeapNode(v, key[v]);
        heap->pos[v] = v + 1;
    }
    
    key[0] = 0;
    decreaseKey(heap, 0, key[0]);
    
    printf("--- Prim's Algorithm Steps ---\n");
    while (!isEmpty(heap)) {
        printHeap(heap);
        HeapNode* heapNode = extractMin(heap);
        int u = heapNode->vertex;
        free(heapNode);
        
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0) {
                if (inHeap(heap, v) && graph[u][v] < key[v]) {
                    key[v] = graph[u][v];
                    parent[v] = u;
                    decreaseKey(heap, v, key[v]);
                }
            }
        }
    }
    
    printf("\n--- Minimum Spanning Tree (Final MST) ---\n");
    printf("Edge \tWeight\n");
    int total_weight = 0;
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        total_weight += graph[i][parent[i]];
    }
    printf("Total MST Weight: %d\n", total_weight);
    free(heap);
}

int main() {
    int V = 9;
    int graph[MAX][MAX];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }
    
    graph[0][1] = 4;  graph[1][0] = 4;  // a - b (4)
    graph[0][7] = 8;  graph[7][0] = 8;  // a - h (8)
    graph[1][2] = 8;  graph[2][1] = 8;  // b - c (8)
    graph[1][7] = 11; graph[7][1] = 11; // b - h (11)
    graph[2][3] = 7;  graph[3][2] = 7;  // c - d (7)
    graph[2][5] = 4;  graph[5][2] = 4;  // c - f (4)
    graph[2][8] = 2;  graph[8][2] = 2;  // c - i (2)
    graph[3][4] = 9;  graph[4][3] = 9;  // d - e (9)
    graph[3][5] = 14; graph[5][3] = 14; // d - f (14)
    graph[4][5] = 10; graph[5][4] = 10; // e - f (10)
    graph[5][6] = 2;  graph[6][5] = 2;  // f - g (2)
    graph[6][7] = 1;  graph[7][6] = 1;  // g - h (1)
    graph[6][8] = 6;  graph[8][6] = 6;  // g - i (6)
    graph[7][8] = 7;  graph[8][7] = 7;  // h - i (7)
    
    primMST(graph, V);
    return 0;
}
