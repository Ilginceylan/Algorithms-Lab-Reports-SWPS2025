#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void fillArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n * 10);
    }
}

int main(void) {
    int testCases[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    srand((unsigned int)time(0));
    printf("Algorithm Runtime Comparison\n\n");
    
    for (int i = 0; i < numTests; i++) {
        int n = testCases[i];
        int* arr = malloc(n * sizeof(int));
        fillArray(arr, n);
        int key = arr[n - 1];
        
        clock_t start, end;
        double time_used;
        
        // --- LINEAR SEARCH ---
        start = clock();
        linearSearch(arr, n, key);
        end = clock();
        time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Linear Search (n=%d): %.6f sec\n", n, time_used);
        
        // --- INSERTION SORT ---
        if (n <= 100000) {
            start = clock();
            insertionSort(arr, n);
            end = clock();
            time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("Insertion Sort (n=%d): %.6f sec\n", n, time_used);
        } else {
            printf("Insertion Sort (n=%d): Skipped (Too slow)\n", n);
        }
        
        // --- BINARY SEARCH ---
        start = clock();
        binarySearch(arr, n, key);
        end = clock();
        time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Binary Search (n=%d): %.6f sec\n", n, time_used);
        
        printf("-----\n");
        free(arr);
    }
    return 0;
}
