#include <stdio.h>

int binarySearchRecursive(int A[], int low, int high, int x) {
    printf("low=%d , high=%d \n", low, high);
    if (low > high) return -1;
    int mid = (low + high) / 2;
    if (A[mid] == x) return mid;
    if (A[mid] < x) return binarySearchRecursive(A, mid + 1, high, x);
    return binarySearchRecursive(A, low, mid - 1, x);
}

int main(void) {
    int A[] = {2, 5, 8, 12, 16, 23, 38};
    int n = 7;
    int x = 23; 

    int result = binarySearchRecursive(A, 0, n - 1, x);

    if (result != -1) printf("Element found at index %d\n", result);
    else printf("Element not found\n");
    return 0;
}