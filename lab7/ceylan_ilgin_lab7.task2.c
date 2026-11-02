#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r) {
    int x = A[r]; 
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}

int randomized_partition(int A[], int p, int r) {
    int i = p + rand() % (r - p + 1);
    swap(&A[i], &A[r]);
    return partition(A, p, r);
}

void print_subarray(int A[], int p, int r) {
    printf("Partitioning subarray [p=%d, r=%d]: ", p, r);
    for (int j = p; j <= r; j++) {
        printf("%d ", A[j]);
    }
    printf("\n");
}

int randomized_select(int A[], int p, int r, int i) {
    print_subarray(A, p, r);

    if (p == r)
        return A[p];

    int q = randomized_partition(A, p, r);
    int k = q - p + 1; 

    if (i == k)
        return A[q];
    else if (i < k)
        return randomized_select(A, p, q - 1, i);
    else
        return randomized_select(A, q + 1, r, i - k);
}

int main() {
    int n = 100;
    int A[100];
    int target_rank = 20; 

    srand(time(NULL));

    printf("INITIAL RANDOM ARRAY (100)\n");
    for (int j = 0; j < n; j++) {
        A[j] = rand() % (100 - 10 + 1) + 10;
        printf("%d ", A[j]);
        if ((j + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    printf("TRACING RANDOMIZED-SELECT (Finding %dth smallest)\n", target_rank);
    int result = randomized_select(A, 0, n - 1, target_rank);

    printf("\nRESULT: The %dth smallest element is: %d\n", target_rank, result);

    return 0;
}