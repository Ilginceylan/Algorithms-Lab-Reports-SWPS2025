#include <stdio.h>

int LEFT(int i) {
    return 2 * i;
}

int RIGHT(int i) {
    return 2 * i + 1;
}

void maxHeapify(int A[], int i, int heap_size) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;
    
    if (l <= heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
        
    if (r <= heap_size && A[r] > A[largest])
        largest = r;
        
    if (largest != i) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        printf("\nThe node is the largest and it may be exchanged with the root is: %d", A[i]);
        maxHeapify(A, largest, heap_size);
    }
}

int main(void) {
    int A[] = {-1000, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int heap_size = sizeof(A) / sizeof(A[0]) - 1;
    int i = 2;
    
    printf("The node violated the max heap property is: %d", A[i]);
    printf("\nBefore MAX-HEAPIFY: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    maxHeapify(A, i, heap_size);
    
    printf("After MAX-HEAPIFY: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    return 0;
}
