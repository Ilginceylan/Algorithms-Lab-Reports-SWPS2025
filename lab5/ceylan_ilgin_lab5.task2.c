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
        maxHeapify(A, largest, heap_size);
    }
}

void buildMaxheap(int A[], int lenght) {
    int heap_size = lenght;
    for (int i = (lenght / 2); i >= 1; i--) {
        printf("\nThe root that we run maxHeapify on it is %d ", A[i]);
        maxHeapify(A, i, heap_size);
    }
}

int main(void) {
    int A[] = {-1000, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int heap_size = sizeof(A) / sizeof(A[0]) - 1;
    
    printf("Original array: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    buildMaxheap(A, heap_size);
    
    printf("\nMax-Heap array: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    return 0;
}
