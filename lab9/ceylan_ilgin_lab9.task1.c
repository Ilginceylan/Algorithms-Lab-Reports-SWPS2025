#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int extended_bottom_up_cut_rod(int p[], int n, int r[], int s[]) {
    r[0] = 0;
    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        int best_i = 1;
        for (int i = 1; i <= j; i++) {
            int val = p[i] + r[j - i];
            if (val > q) {
                q = val;
                best_i = i;
            }
        }
        r[j] = q;
        s[j] = best_i;
    }
    return r[n];
}

void print_cut_solution(int s[], int n) {
    printf("Optimal cuts: ");
    int first = 1;
    while (n > 0) {
        if (!first) 
            printf(" + ");
        printf("%d", s[n]);
        first = 0;
        n -= s[n];
    }
    printf("\n");
}

int main() {
    int p[] = {0, 2, 4, 8, 8, 10, 20, 21, 25, 28, 29};
    int n = 10;
    int r[11], s[11];
    
    printf("--- Task 1: Rod-Cutting ---\n");
    int max_rev = extended_bottom_up_cut_rod(p, n, r, s);
    printf("Maximum revenue: %d\n", max_rev);
    print_cut_solution(s, n);
    
    return 0;
}
