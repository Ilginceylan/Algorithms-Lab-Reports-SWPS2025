#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

void tree_insert(node **root, int key) {
    node *z = (node*)malloc(sizeof(node));
    z->key = key;
    z->left = z->right = z->parent = NULL;

    node *y = NULL;
    node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z; 
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}

void inorder_tree_walk(node *x) {
    if (x != NULL) {
        inorder_tree_walk(x->left);
        printf("%d ", x->key);
        inorder_tree_walk(x->right);
    }
}

node* tree_search(node *x, int k) {
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return tree_search(x->left, k);
    else
        return tree_search(x->right, k);
}

node* tree_minimum(node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

node* tree_maximum(node *x) {
    while (x->right != NULL)
        x = x->right;
    return x;
}

node* tree_successor(node *x) {
    if (x->right != NULL)
        return tree_minimum(x->right);

    node *y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void transplant(node **root, node *u, node *v) {
    if (u->parent == NULL) {
        *root =v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }

    if (v != NULL)
        v->parent = u->parent;
}

void tree_delete(node **root, node *z) {
    if (z->left == NULL) {

        printf("Case 1: no left child");
        transplant(root, z, z->right);
    } else if (z->right == NULL) {
        printf("Case 2: no right child");
        transplant(root, z, z->left);

    } else {
        printf("Case 3: two children");
        node *y = tree_minimum(z->right);

        if (y->parent != z) {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
}

int main() {
    node *root = NULL;

    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2};
    for(int i = 0; i < 8; i++) {
        tree_insert(&root, keys[i]);
    }

    printf("Task 2 - Inorder Traversal: ");
    inorder_tree_walk(root);
    printf("\n\n");

    int search_keys[] = {17, 2};
    for(int i = 0; i < 2; i++) {
        node* found = tree_search(root, search_keys[i]);
        if(found) printf("Task 3: Key %d found in tree.\n", search_keys[i]);
        else printf("Task 3: Key %d NOT found.\n", search_keys[i]);
    }
    printf("\n");

    printf("Task 4 - Minimum: %d\n", tree_minimum(root)->key);
    printf("Task 4 - Maximum: %d\n", tree_maximum(root)->key);
    int succ_targets[] = {3, 7, 15, 2};
    for(int i = 0; i < 4; i++) {
        node* target = tree_search(root, succ_targets[i]);
        node* succ = tree_successor(target);
        if(succ) printf("Successor of %d is %d\n", succ_targets[i], succ->key);
        else printf("Successor of %d is NULL\n", succ_targets[i]);
    }
    printf("\n");

    int delete_keys[] = {18, 6};
    for(int i = 0; i < 2; i++) {
        printf("Deleting %d...\n", delete_keys[i]);
        node* target = tree_search(root, delete_keys[i]);
        tree_delete(&root, target);
        printf("\nInorder after deletion: ");
        inorder_tree_walk(root);
        printf("\n");
    }

    return 0;
}
