#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node* prev;
    struct node* next;
}; 

struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
} 

struct node* insertBegin(struct node* head, int key) {
    struct node* x = createNode(key);
    x->next = head;
    if (head != NULL) {
        head->prev = x;
    }
    return x;
} 

struct node* insertEnd(struct node* head, int key) {
    struct node* x = createNode(key);
    if (head == NULL) {
        return x;
    }
    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = x;
    x->prev = temp;
    return head;
} 

void insertAfter(struct node* y, int key) {
    if (y == NULL) return;
    struct node* x = createNode(key);
    x->next = y->next;
    x->prev = y;
    if (y->next != NULL) {
        y->next->prev = x;
    }
    y->next = x;
} 

struct node* search(struct node* head, int key) {
    struct node* temp = head;
    while (temp != NULL) {
        if (temp->key == key) {
            printf("Found: %d\n", temp->key);
            return temp;
        }
        temp = temp->next;
    }
    printf("Not found\n");
    return NULL;
} 

struct node* deleteNode(struct node* head, int key) {
    struct node* x = search(head, key);
    if (x == NULL) {
        printf("Value not found in list.\n");
        return head;
    }
    if (x->prev != NULL) {
        x->prev->next = x->next;
    } else {
        head = x->next; 
    }
    if (x->next != NULL) {
        x->next->prev = x->prev;
    }
    free(x);
    return head;
} 

void displayForward(struct node* head) {
    struct node* temp = head;
    printf("List (forward): ");
    while (temp != NULL) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
} 

void freeList(struct node* head) {
    struct node* temp = head;
    struct node* next;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
} 

int main(void) {
    struct node* head = NULL;
    struct node* temp = NULL;

    head = insertBegin(head, 5);
    displayForward(head);

    head = insertBegin(head, 20);
    displayForward(head);

    head = insertEnd(head, 40);
    displayForward(head);

    head = insertEnd(head, 60);
    displayForward(head);

    temp = search(head, 20);
    if (temp != NULL) {
        insertAfter(temp, 80);
        displayForward(head);
    }

    head = deleteNode(head, 40);
    displayForward(head);

    freeList(head);
    return 0;
} 
