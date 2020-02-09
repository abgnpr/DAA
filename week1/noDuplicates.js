function noDuplicates(A) {
    for (let i = 0; i < A.length; ++i) {
        for (let j = i + 1; j < A.length; ++j) {
            if (A[i] == A[j])
                return false
        }
    }
    return true
}

let A = ['A', 'B', 'C', 'D']
if (noDuplicates(A))
    console.log("Good");
else 
    console.log("Duplicate found");