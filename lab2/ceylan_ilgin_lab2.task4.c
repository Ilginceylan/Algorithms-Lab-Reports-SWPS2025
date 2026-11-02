#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void m_merge(int A[], int p, int q, int r) {
    int n1=q-p+1, n2=r-q;
    int *L=malloc(n1*4), *R=malloc(n2*4);
    for(int i=0;i<n1;i++) L[i]=A[p+i];
    for(int j=0;j<n2;j++) R[j]=A[q+1+j];
    int i=0,j=0,k=p;
    while(i<n1&&j<n2) A[k++]=(L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) A[k++]=L[i++]; while(j<n2) A[k++]=R[j++];
    free(L); free(R);
}
void m_sort(int A[], int p, int r) { if(p<r){int q=(p+r)/2; m_sort(A,p,q); m_sort(A,q+1,r); m_merge(A,p,q,r);}}
int q_part(int A[], int p, int r) {
    int x=A[r], i=p-1;
    for(int j=p;j<r;j++) if(A[j]<=x){i++; int t=A[i]; A[i]=A[j]; A[j]=t;}
    int t=A[i+1]; A[i+1]=A[r]; A[r]=t; return i+1;
}
void q_sort(int A[], int p, int r) { if(p<r){int q=q_part(A,p,r); q_sort(A,p,q-1); q_sort(A,q+1,r);}}

int main() {
    int sizes[] = {10, 100, 1000, 5000, 10000};
    printf("%-10s | %-15s | %-15s\n", "Input size", "Merge Sort (sn)", "Quick Sort (sn)");
    for(int i=0; i<5; i++) {
        int n = sizes[i];
        int *a1=malloc(n*4), *a2=malloc(n*4);
        for(int j=0; j<n; j++) a1[j]=a2[j]=rand()%10000;
        clock_t s1=clock(); m_sort(a1,0,n-1); double t1=(double)(clock()-s1)/CLOCKS_PER_SEC;
        clock_t s2=clock(); q_sort(a2,0,n-1); double t2=(double)(clock()-s2)/CLOCKS_PER_SEC;
        printf("%-10d | %-15.6f | %-15.6f\n", n, t1, t2);
        free(a1); free(a2);
    }
    return 0;
}