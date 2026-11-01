#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
} 

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) { 
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
} 

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high); 
    }
}

void printArr(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
} 

int main() {
    int arr[] = {12, 4, 6, 9, 1, 3}; 
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArr(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    printArr(arr, n);

    return 0;
} 