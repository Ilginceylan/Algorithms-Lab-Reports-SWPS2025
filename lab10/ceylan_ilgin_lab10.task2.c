#include <stdio.h>

#define MAX 20

int activity_selection(int s[], int f[], int n, int selected[]) {
    int k = 1;
    selected[0] = 1;
    int count = 1;
    
    for (int m = 2; m <= n; m++) {
        if (s[m] >= f[k]) {
            selected[count] = m;
            k = m;
            count++;
        }
    }
    return count;
}

int main() {
    int n = 15;
    int start_time[]  = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 14, 15, 18, 19};
    int finish_time[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 17, 19, 21, 23};
    int selected[MAX];
    
    printf("Executing Greedy Activity Selection...\n");
    printf("Total activities to process: %d\n\n", n);
    
    int total_selected = activity_selection(start_time, finish_time, n, selected);
    
    printf("--- Selected Maximum Set of Mutually Compatible Activities ---\n");
    printf("Activity\tStart Time\tFinish Time\n");
    for (int i = 0; i < total_selected; i++) {
        int act_num = selected[i];
        printf("A%d\t\t%d\t\t%d\n", act_num, start_time[act_num], finish_time[act_num]);
    }
    printf("Total mutually compatible activities selected: %d\n", total_selected);
    
    return 0;
}
