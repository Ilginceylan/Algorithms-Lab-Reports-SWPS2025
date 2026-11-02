#include <stdio.h>
#include <stdlib.h>

int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    printf(" p= %d, r= %d and the pivot is: %d \n", p, r, x);
    for (int j = p; j <= r; j++) printf("%d ", A[j]);

    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;

    printf("\n[");
    for (int j = p; j <= r; j++) {
        if (j == i + 1) printf("]");
        printf("%d ", A[j]);
        if (j == i + 1) printf("[");
    }
    printf("] division point: %d \n\n", i + 1);
    return i + 1;
}

void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int main(void) {
    int n = 10;
    int A[] = {7, 49, 73, 58, 30, 72, 44, 78, 23, 9};
    quickSort(A, 0, n - 1);
    return 0;
}