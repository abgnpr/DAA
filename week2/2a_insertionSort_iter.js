function swap(A, x, y) {
    let temp = A[x]
    A[x] = A[y]
    A[y] = temp
}

function insertionSort(A, n) {
    for ( let pos = 1; pos < n; ++pos ) {
        let nextpos = pos;
        while (nextpos > 0 && A[nextpos] < A[nextpos-1]) {
            swap(A, nextpos, nextpos-1)
            nextpos = nextpos - 1;
        }
    }
}

let A = [ 32, 74, 89, 55, 21, 64 ]

insertionSort(A, A.length)

for (const element of A)
    console.log(element);