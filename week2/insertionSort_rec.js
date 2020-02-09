function swap(A, x, y) {
    let temp = A[x]
    A[x] = A[y]
    A[y] = temp
}

// insert A[pos] into A[0 ... pos-1]
function insert(A, pos) {
    while (pos > 0 && A[pos] < A[pos - 1]) {
        swap(A, pos, pos - 1)
        pos = pos - 1;
    }
}

// sort A from start to n-1
function insertionSort(A, start, n) {
    if (start > n-1)
        return
    insert(A, start)
    insertionSort(A, start + 1, n)
    return
}


let A = [32, 74, 89, 55, 21, 64]
let start = 1

insertionSort(A, start, A.length)

for (const element of A)
    console.log(element);