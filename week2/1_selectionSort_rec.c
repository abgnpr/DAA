#include <stdio.h>

void swap(int A[], int start, int minpos) {
    int temp = A[start];
    A[start] = A[minpos];
    A[minpos] = temp;
}

void selectionSort(int A[], int start, int n) {
    if (start > n - 1)
        return;

    int minpos = start;
    for (int i = start + 1; i < n; ++i)
        if (A[i] < A[minpos])
            minpos = i;

    swap(A, start, minpos);

    selectionSort(A, start + 1, n);
}

void main(void) {
    int A[] = {5, 18, 2, 66, 9, 10};
    int len = sizeof(A) / sizeof(A[0]);
    selectionSort(A, 0, len);
    for (int i = 0; i < len; ++i)
        printf("%d\n", A[i]);
}