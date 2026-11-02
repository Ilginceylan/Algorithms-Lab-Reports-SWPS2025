#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

int PARENT(int i) {
    return i / 2;
}

int LEFT(int i) {
    return 2 * i;
}

int RIGHT(int i) {
    return 2 * i + 1;
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void maxHeapify(int A[], int i, int heap_size) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;
    
    if (l <= heap_size && A[l] > A[i])
        largest = l;
    if (r <= heap_size && A[r] > A[largest])
        largest = r;
        
    if (largest != i) {
        swap(&A[i], &A[largest]);
        maxHeapify(A, largest, heap_size);
    }
}

int heap_maximum(int A[]) {
    return A[1];
}

int heap_extract_max(int A[], int *heap_size) {
    if (*heap_size < 1) {
        printf("Heap underflow!\n");
        return -1;
    }
    int max = heap_maximum(A);
    A[1] = A[*heap_size];
    (*heap_size)--;
    maxHeapify(A, 1, *heap_size);
    return max;
}

void heap_increase_key(int A[], int i, int key) {
    if (key < A[i]) {
        printf("New key is smaller than current key!\n");
        return;
    }
    printf("The value of A[%d] before increase is: %d\n", i, A[i]);
    A[i] = key;
    printf("The value of A[%d] after increase is: %d\n", i, A[i]);
    
    while (i > 1 && A[PARENT(i)] < A[i]) {
        printf("We need to swap the values of %d, %d\n", A[i], A[PARENT(i)]);
        swap(&A[i], &A[PARENT(i)]);
        i = PARENT(i);
    }
}

void max_heap_insert(int A[], int key, int *heap_size) {
    if (*heap_size >= MAX_SIZE - 1) {
        printf("Heap overflow!\n");
        return;
    }
    (*heap_size)++;
    A[*heap_size] = INT_MIN;
    heap_increase_key(A, *heap_size, key);
}

void heap_decrease_key(int A[], int i, int key, int heap_size) {
    if (key > A[i]) {
        printf("New key is larger than current key!\n");
        return;
    }
    A[i] = key;
    maxHeapify(A, i, heap_size);
}

int main() {
    int A[MAX_SIZE];
    int heap_size = 0;
    int i;
    
    printf("--- Task 1-1: Inserting elements (15, 10, 30, 40, 5) ---\n");
    int data[] = {15, 10, 30, 40, 5};
    for (i = 0; i < 5; i++) {
        printf("\nInserting %d:\n", data[i]);
        max_heap_insert(A, data[i], &heap_size);
        printf("Current heap: ");
        for (int j = 1; j <= heap_size; j++)
            printf("%d ", A[j]);
        printf("\n");
    }
    
    printf("\n--- Task 1-2: Finding Maximum ---\n");
    printf("Maximum element is: %d\n", heap_maximum(A));
    
    printf("\n--- Task 1-3: Extracting Maximum ---\n");
    int extracted = heap_extract_max(A, &heap_size);
    printf("Extracted: %d\n", extracted);
    printf("Heap after extraction: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    printf("\n--- Task 1-4: Increasing index 3 to 35 ---\n");
    heap_increase_key(A, 3, 35);
    printf("Heap after increase-key: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    printf("\n--- Task 1-5: Decreasing index 4 to 2 ---\n");
    heap_decrease_key(A, 4, 2, heap_size);
    printf("Heap after decrease-key: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    return 0;
}
