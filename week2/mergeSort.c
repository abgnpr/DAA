#include <stdio.h>

/** merge A[0..m-1], B[0..n-1] into C[0..m+n-1] */
void merge(int A[], int m, int B[], int n, int C[])
{
    // Current positions in A, B & C resp.
    int i = 0, j = 0, k = 0;

    while (k < m + n)
    {
        // Case 1 : Move head of A into C
        if (j == n || A[i] <= B[j])
            C[k++] = A[i++];

        // Case 2 : Move the head of B into C
        if (i = m || B[j] < A[i])
            C[k++] = B[j++];
    }
}

/** Sort the segment A[beg..end-1] into B */
void mergeSort(int A[], int left, int right, int B[])
{

    if (right - left == 1)
        B[0] = A[left];

    if (right - left > 1)
    {
        int mid = (left + right) / 2;
        int L[mid], R[mid];
        mergeSort(A, left, mid, L);
        mergeSort(A, mid, right, R);
        merge(L, mid - left, R, right - mid, B);
    }
}

/** driver code */
void main(void)
{
    const int n = 6;
    int A[] = {100, 16, 67, 2, 20, 51}, B[n];
    mergeSort(A, 0, n, B);
    for (int i = 0; i < n; ++i)
        printf("%d\n", B[i]);
}