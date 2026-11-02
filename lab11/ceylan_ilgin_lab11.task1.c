#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 200

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    int size;
    Node* array[MAX_SIZE];
} MinHeap;

Node* createNode(char symbol, int freq) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

void swap(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i;
    int right = 2 * i + 1;
    
    if (left <= heap->size && heap->array[left]->freq < heap->array[smallest]->freq) {
        smallest = left;
    }
    if (right <= heap->size && heap->array[right]->freq < heap->array[smallest]->freq) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

Node* extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        return NULL;
    }
    Node* temp = heap->array[1];
    heap->array[1] = heap->array[heap->size];
    heap->size--;
    heapify(heap, 1);
    return temp;
}

void heapInsert(MinHeap* heap, Node* node) {
    heap->size++;
    int i = heap->size;
    while (i > 1 && node->freq < heap->array[i / 2]->freq) {
        heap->array[i] = heap->array[i / 2];
        i = i / 2;
    }
    heap->array[i] = node;
}

void printMinHeap(MinHeap* heap) {
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->array[i]->freq);
    }
    printf("\n");
}

void buildMinHeap(MinHeap* heap) {
    for (int i = heap->size / 2; i >= 1; i--) {
        heapify(heap, i);
    }
}

Node* buildHuffmanTree(char symbols[], int freqs[], int size) {
    MinHeap heap;
    heap.size = size;
    for (int i = 0; i < size; ++i) {
        heap.array[i + 1] = createNode(symbols[i], freqs[i]);
    }
    buildMinHeap(&heap);
    
    while (heap.size > 1) {
        Node* left = extractMin(&heap);
        Node* right = extractMin(&heap);
        Node* z = createNode('$', left->freq + right->freq);
        z->left = left;
        z->right = right;
        heapInsert(&heap, z);
        printf("\nMinheap after inserting the new node: %d\n", z->freq);
        printMinHeap(&heap);
    }
    return extractMin(&heap);
}

void printCodes(Node* root, char code[], int idx) {
    if (!root) {
        return;
    }
    if (!root->left && !root->right) {
        code[idx] = '\0';
        printf("%c: %s\n", root->symbol, code);
        return;
    }
    code[idx] = '0';
    printCodes(root->left, code, idx + 1);
    code[idx] = '1';
    printCodes(root->right, code, idx + 1);
}

int main() {
    char symbols[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(symbols) / sizeof(symbols[0]);
    
    Node* root = buildHuffmanTree(symbols, freqs, size);
    char code[MAX_SIZE];
    
    printf("\nHuffman Codes:\n");
    printCodes(root, code, 0);
    
    return 0;
}
