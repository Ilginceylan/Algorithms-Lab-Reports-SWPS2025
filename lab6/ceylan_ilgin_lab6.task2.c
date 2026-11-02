#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void counting_sort(int A[], int B[], int n, int k) {
    int *C = (int*)malloc((k + 1) * sizeof(int));
    for (int i = 0; i <= k; i++)
        C[i] = 0;
        
    for (int j = 0; j < n; j++)
        C[A[j]] = C[A[j]] + 1;
        
    printf("\nStep 2: array C after counting each element's frequency is: ");
    print_array(C, k + 1);
    
    printf("Step 3: compute the cumulative counts of array C step by step\n");
    for (int i = 1; i <= k; i++) {
        C[i] = C[i] + C[i - 1];
        print_array(C, k + 1);
    }
    
    for (int j = n - 1; j >= 0; j--) {
        printf("\n----- Step 4 -----\n");
        printf("array A is: ");
        print_array(A, n);
        printf("array C is: ");
        print_array(C, k + 1);
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
        printf("array B is: ");
        print_array(B, n);
    }
    free(C);
}

int main() {
    int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 5;
    int B[8];
    
    printf("--- Task 2-1: Counting Sort ---\n");
    printf("Original array A: ");
    print_array(A, n);
    
    counting_sort(A, B, n, k);
    
    printf("\nFinal sorted array B: ");
    print_array(B, n);
    
    return 0;
}
