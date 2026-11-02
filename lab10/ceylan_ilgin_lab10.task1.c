#include <stdio.h>
#include <string.h>

#define MAX 100

void print_lcs(int b[MAX][MAX], char X[], int i, int j) {
    if (i == 0 || j == 0) 
        return;
    if (b[i][j] == 1) {
        print_lcs(b, X, i - 1, j - 1);
        printf("%c", X[i - 1]);
    } else if (b[i][j] == 2) {
        print_lcs(b, X, i - 1, j);
    } else {
        print_lcs(b, X, i, j - 1);
    }
}

int lcs_length(char X[], char Y[]) {
    int m = (int)strlen(X);
    int n = (int)strlen(Y);
    int c[MAX][MAX];
    int b[MAX][MAX];
    
    for (int i = 0; i <= m; i++) 
        c[i][0] = 0;
    for (int j = 0; j <= n; j++) 
        c[0][j] = 0;
        
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            } else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
    }
    
    printf("\nLCS Length Table (c)\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    printf("\nDirection Table (b) [1:Diag, 2:Up, 3:Left]\n");
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
    
    printf("\nLCS: ");
    print_lcs(b, X, m, n);
    printf("\n");
    
    return c[m][n];
}

int main() {
    char string1[] = "ATCGGCTAATCGATCGGCTAATCGATCGG";
    char string2[] = "TCGGCTAATCGATCGGCTAATCGATCGGC";
    
    printf("String 1: %s\n", string1);
    printf("String 2: %s\n", string2);
    
    int length = lcs_length(string1, string2);
    printf("Total LCS Length: %d\n", length);
    
    return 0;
}
