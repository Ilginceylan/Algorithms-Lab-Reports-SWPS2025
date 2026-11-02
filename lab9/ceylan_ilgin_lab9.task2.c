#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

void print_optimal_parens(int s[MAX][MAX], int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

void print_m_table(int m[MAX][MAX], int n) {
    printf("\nDP Table m[i][j] (Minimum Costs):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i)
                printf("      ");
            else
                printf("%5d ", m[i][j]);
        }
        printf("\n");
    }
}

void print_s_table(int s[MAX][MAX], int n) {
    printf("\nSplit Table s[i][j] (Optimal Splits):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j <= i)
                printf("  ");
            else
                printf("%d ", s[i][j]);
        }
        printf("\n");
    }
}

int matrix_chain_order(int p[], int n) {
    int m[MAX][MAX];
    int s[MAX][MAX];
    
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;
        
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
    
    print_m_table(m, n);
    print_s_table(s, n);
    printf("\nOptimal Parenthesization: ");
    print_optimal_parens(s, 1, n);
    printf("\n");
    
    return m[1][n];
}

int main() {
    int p[] = {10, 20, 100, 1, 50};
    int n = 4;
    
    printf("\n--- Task 2: Matrix Chain Multiplication ---\n");
    matrix_chain_order(p, n);
    
    return 0;
}
