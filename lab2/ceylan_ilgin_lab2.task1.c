#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Memory allocation failed\n");
        exit(0);
    }

    printf("\nThe left subarray for merging is : ");
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
        printf("%d ", L[i]);
    }

    printf("\nThe right subarray for merging is : ");
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
        printf("%d ", R[j]);
    }

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        } else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    printf("\nsubarrays after merging: ");
    for (int i = p; i <= r; i++) printf("%d ", A[i]);

    free(L);
    free(R);
}

void mergeSort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        printf("\nThe left sub problem is A[ %d .. %d]", p, q);
        mergeSort(A, p, q);
        printf("\nThe right sub problem is A[ %d .. %d]", q + 1, r);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main(void) {
    int n = 10;
    int A[] = {7, 49, 73, 58, 30, 72, 44, 78, 23, 9};

    printf("The unsorted array is : ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    mergeSort(A, 0, n - 1);
    
    printf("\n\nFinal Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");

    return 0;
}
