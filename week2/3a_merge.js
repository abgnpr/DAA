// MERGE SORT

/** Merge A[0 .. m-1] & B[0 .. n-1] 
 *  into C[0 .. m+n-1  */
function merge(A, m, B, n, C) {

    // Current positions in A, B & C resp.
    let i = 0, j = 0, k = 0

    while (k < m + n) {

        // Case 1 : move head of A into C
        if (j == n || A[i] <= B[j])
            C[k++] = A[i++]

        // Case 2 : move head of B into C
        if (i == m || A[i] > B[j])
            C[k++] = B[j++]

    }
}

// driver
let 
    m = 3, n = 4,
    A = [2, 4, 6],
    B = [1, 3, 5, 7],
    C = []

merge(A, m, B, n, C)

C.forEach(e => console.log(e));
