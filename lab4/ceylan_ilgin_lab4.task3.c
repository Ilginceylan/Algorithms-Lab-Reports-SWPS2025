#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int parent;
    int rank;
} Node;

Node* make_set(int n) {
    Node *S = (Node *)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        S[i].parent = i;
        S[i].rank = 0;
    }
    return S;
}

int find_naive(Node *S, int x) {
    if (S[x].parent == x) 
        return x;
    return find_naive(S, S[x].parent);
}

void union_naive(Node *S, int x, int y) {
    int rx = find_naive(S, x);
    int ry = find_naive(S, y);
    if (rx != ry) 
        S[ry].parent = rx;
}

void print_sets(Node *S, int n) {
    int *visited = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        int root = find_naive(S, i);
        if (!visited[root]) {
            printf("Friendship group (Root %d): ", root + 1);
            for (int j = 0; j < n; j++) {
                if (find_naive(S, j) == root) {
                    printf("%d ", j + 1);
                }
            }
            printf("\n");
            visited[root] = 1;
        }
    }
    free(visited);
}

int main() {
    int n = 6;
    Node *S = make_set(n);
    
    union_naive(S, 1 - 1, 3 - 1); // 1-3
    union_naive(S, 3 - 1, 4 - 1); // 3-4
    union_naive(S, 1 - 1, 2 - 1); // 1-2
    union_naive(S, 5 - 1, 6 - 1); // 5-6
    
    printf("Friendship Groups:\n");
    print_sets(S, n);
    
    free(S);
    return 0;
}
