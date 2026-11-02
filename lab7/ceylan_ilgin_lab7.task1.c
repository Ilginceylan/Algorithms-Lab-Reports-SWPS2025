#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    float value;
    struct Node* next;
} Node;

void printBucket(Node* head) {
    if (head == NULL) {
        printf("Empty");
    } else {
        Node* temp = head;
        while (temp != NULL) {
            printf("%.4f ", temp->value);
            if(temp->next != NULL) printf("-> ");
            temp = temp->next;
        }
    }
    printf("\n");
}

Node* insert_sorted(Node* head, float value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL || value < head->value) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    return head;
}

void bucketSort(float arr[], int n) {
    
    Node** buckets = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) buckets[i] = NULL;

    printf("\nDISTRIBUTING ELEMENTS INTO BUCKETS\n");

    for (int i = 0; i < n; i++) {
        int index = (int)(n * arr[i]);
        if (index >= n) index = n - 1;

        buckets[index] = insert_sorted(buckets[index], arr[i]);

        printf("Element %.4f added to Bucket [%d]. Current Bucket: ", arr[i], index);
        printBucket(buckets[index]);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        Node* current = buckets[i];
        while (current != NULL) {
            arr[k++] = current->value;
            current = current->next;
        }
    }

    for (int i = 0; i < n; i++) {
        Node* current = buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}

int main() {
    int n = 50; 
    float arr[50];
    
    srand(time(NULL));

    printf("INITIAL RANDOM ARRAY (50)\n");
    for (int i = 0; i < n; i++) {
        arr[i] = (float)rand() / (float)RAND_MAX; 
        printf("%.4f  ", arr[i]);
        if ((i + 1) % 5 == 0) printf("\n"); 
    }

    bucketSort(arr, n);

    printf("\nFINAL SORTED ARRAY\n");
    for (int i = 0; i < n; i++) {
        printf("%.4f  ", arr[i]);
        if ((i + 1) % 5 == 0) printf("\n");
    }

    return 0;
}
