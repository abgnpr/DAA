// MERGE SORT

/** Merge A[0 .. m-1] & B[0 .. n-1] 
 *  into C[0 .. m+n-1  */
function merge(A, m, B, n, C) {
    let i = 0, j = 0, k = 0
    while (k < m + n) {
        if (j == n || A[i] <= B[j])
            C[k++] = A[i++]
        if (i == m || A[i] > B[j])
            C[k++] = B[j++]
    }
}

function mergeSort(A, left, right, B) {

    // base case
    if (right - left == 1)
        B[0] = A[left]

    // recursive call
    if (right - left > 1) {
        let mid = (left + right) / 2
        let L = [], R = []
        mergeSort(A, left, mid, L)
        mergeSort(A, mid, right, R)
        merge(L, mid - left, R, right - mid, B)
    }

    return
}

// driver
let A = [43, 32, 22, 78, 63, 57, 91, 13]
let B = []
mergeSort(A, 0, A.length, B)

B.forEach(e => console.log(e));
