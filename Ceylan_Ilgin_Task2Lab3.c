#include <stdio.h>
#include <stdlib.h>

#define MAX 100 

typedef struct {
    int A[MAX];
    int head;
    int tail;
} Queue; 

void initQueue(Queue *Q) {
    Q->head = 0;
    Q->tail = 0;
} 

int queueEmpty(Queue *Q) {
    return (Q->head == Q->tail);
} 

void enqueue(Queue *Q, int x) {
    if ((Q->tail + 1) % MAX == Q->head) { 
        printf("Error: Queue overflow\n");
        return;
    }
    Q->A[Q->tail] = x; 
    Q->tail = (Q->tail + 1) % MAX; 
}

int dequeue(Queue *Q) {
    if (queueEmpty(Q)) { 
        printf("Error: Queue underflow\n");
        return -1;
    }
    int x = Q->A[Q->head]; 
    Q->head = (Q->head + 1) % MAX; 
    return x;
}

void printqueue(Queue *Q) {
    if (!queueEmpty(Q)) { 
        printf("Current Queue is : ");
        int i = Q->head;
        while (i != Q->tail) { 
            printf("%d ", Q->A[i]); 
            i = (i + 1) % MAX; 
        }
        printf("\n"); 
    } else {
        printf("Queue is empty\n"); 
    }
}

int main(void) {
    Queue Q;
    initQueue(&Q); 

    enqueue(&Q, 10); 
    printqueue(&Q); 

    enqueue(&Q, 20); 
    printqueue(&Q); 

    enqueue(&Q, 30); 
    printqueue(&Q); 

    printf("Dequeued: %d\n", dequeue(&Q)); 
    printqueue(&Q); 

    printf("Dequeued: %d\n", dequeue(&Q)); 
    printqueue(&Q); 

    printf("Dequeued: %d\n", dequeue(&Q)); 
    printqueue(&Q); 

    return 0;
}