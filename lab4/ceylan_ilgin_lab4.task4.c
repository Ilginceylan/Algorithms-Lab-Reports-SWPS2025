#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int find_opt(Node *S, int x) {
    if (S[x].parent != x) 
        S[x].parent = find_opt(S, S[x].parent);
    return S[x].parent;
}

void union_opt(Node *S, int x, int y) {
    int rx = find_opt(S, x);
    int ry = find_opt(S, y);
    if (rx != ry) {
        if (S[rx].rank > S[ry].rank) {
            S[ry].parent = rx;
        } else {
            S[rx].parent = ry;
            if (S[rx].rank == S[ry].rank) 
                S[ry].rank++;
        }
    }
}

int main() {
    int n = 100;
    Node *S = make_set(n);
    srand(time(NULL));
    
    printf("Generating 50 random friendships...\n");
    for (int i = 0; i < 50; i++) {
        int u = rand() % n;
        int v = rand() % n;
        union_opt(S, u, v);
    }
    
    int *visited = (int *)calloc(n, sizeof(int));
    printf("\nFriendship Network Results (Size 100):\n");
    for (int i = 0; i < n; i++) {
        int root = find_opt(S, i);
        if (!visited[root]) {
            printf("Group: ");
            for (int j = 0; j < n; j++) {
                if (find_opt(S, j) == root) 
                    printf("%d ", j);
            }
            printf("\n");
            visited[root] = 1;
        }
    }
    
    free(visited);
    free(S);
    return 0;
}
