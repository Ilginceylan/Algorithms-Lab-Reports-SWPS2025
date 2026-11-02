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

void buildMaxHeap(int A[], int length) {
    for (int i = length / 2; i >= 1; i--) {
        maxHeapify(A, i, length);
    }
}

void heapSort(int A[], int lenght) {
    buildMaxHeap(A, lenght);
    int heap_size = lenght;
    
    for (int i = lenght; i >= 2; i--) {
        printf("\nThe elements in the heap after maxHeapify: ");
        for (int j = 1; j <= heap_size; j++)
            printf("%d ", A[j]);
            
        int temp = A[1];
        A[1] = A[i];
        A[i] = temp;
        heap_size--;
        
        printf("\nThe elements in the heap left after exchange: ");
        for (int j = 1; j <= heap_size; j++)
            printf("%d ", A[j]);
    }
    printf("\n");
}

int main(void) {
    int A[] = {-1000, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int heap_size = sizeof(A) / sizeof(A[0]) - 1;
    
    printf("Original array: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    heapSort(A, heap_size);
    
    printf("Sorted array: ");
    for (int j = 1; j <= heap_size; j++)
        printf("%d ", A[j]);
    printf("\n");
    
    return 0;
}
