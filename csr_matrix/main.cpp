#include <iostream>
#include <vector>
#include "cmath"
#include "csr_matrix.h"
using namespace std;

int main() {
    //vector<double>mtx = { 0, 0, 0, 5, 0, 2, 0, 0, 1, 3, 0, 0, 0, 0, 4, 0};
    //csrMatrix::MtxToCSR(mtx);
    csrMatrix::csrMatrix<int> matrix(3); // 3×3 matrix of integers
    csrMatrix::csrMatrix<int> matrix2(4, 5); // 4×5 matrix - 4 rows, 5 columns
    int val;
    matrix.set(-5, 2, 3); // sets -5 on 2nd row and 3rd column
    val = matrix.get(2, 3); // val = -5
    cout << val << "\n";
    csrMatrix::csrMatrix<int> mat(4, 5);
    vector<int> vec(5, 2);

    vector<int> result;
    result = mat.multiply(vec); // method
    //result = mat * vec; // operator
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << '\n';
    /*
    csrMatrix::csrMatrix<int> matrixA(2, 3);
    csrMatrix::csrMatrix<int> matrixB(3, 4);
    csrMatrix::csrMatrix<int> product; // will be of size 2×4
    product = matrixA.multiply(matrixB); // method
    product = matrixA * matrixB; // operator
    */
    return 0;
}
