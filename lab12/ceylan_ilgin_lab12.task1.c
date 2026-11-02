#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define dim 9

int time_counter;
int finish_order[dim];
int finish_count = 0;

void DFS_VISIT(int u, int adj[][dim], int color[], int d[], int parent[], int f[], int n) {
    color[u] = GRAY;
    time_counter++;
    d[u] = time_counter;
    
    for (int v = 0; v < n; v++) {
        if (adj[u][v] == 1 && color[v] == WHITE) {
            parent[v] = u;
            DFS_VISIT(v, adj, color, d, parent, f, n);
        }
    }
    color[u] = BLACK;
    time_counter++;
    f[u] = time_counter;
    finish_order[finish_count++] = u;
}

void DFS(int adj[][dim], int n, int d[], int f[], int parent[]) {
    int color[dim];
    for (int u = 0; u < n; u++) {
        color[u] = WHITE;
        parent[u] = -1;
    }
    time_counter = 0;
    finish_count = 0;
    
    for (int u = 0; u < n; u++) {
        if (color[u] == WHITE) {
            DFS_VISIT(u, adj, color, d, parent, f, n);
        }
    }
}

void transposeGraph(int adj[][dim], int trans[][dim], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            trans[i][j] = adj[j][i];
        }
    }
}

void DFS_VISIT_SCC(int u, int adj[][dim], int color[], int n) {
    color[u] = GRAY;
    printf("%d ", u);
    
    for (int v = 0; v < n; v++) {
        if (adj[u][v] == 1 && color[v] == WHITE) {
            DFS_VISIT_SCC(v, adj, color, n);
        }
    }
    color[u] = BLACK;
}

void STRONGLY_CONNECTED_COMPONENTS(int adj[][dim], int n) {
    int d[dim], f[dim], parent[dim];
    DFS(adj, n, d, f, parent);
    
    printf("Nodes Finish Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: %d\n", i, f[i]);
    }
    
    int trans[dim][dim];
    transposeGraph(adj, trans, n);
    
    int color[dim];
    for (int i = 0; i < n; i++) {
        color[i] = WHITE;
    }
    
    printf("\nStrongly Connected Components:\n");
    int component_num = 1;
    
    for (int i = finish_count - 1; i >= 0; i--) {
        int u = finish_order[i];
        if (color[u] == WHITE) {
            printf("Component %d: ", component_num++);
            DFS_VISIT_SCC(u, trans, color, n);
            printf("\n");
        }
    }
}

int main() {
    int adj[dim][dim] = {
        {0,1,1,0,0,0,0,0,0},
        {1,0,0,0,0,1,0,0,0},
        {1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,1,0,0},
        {0,1,0,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,1,0},
        {0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,1,0}
    };
    
    STRONGLY_CONNECTED_COMPONENTS(adj, dim);
    return 0;
}
