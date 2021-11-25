//
// Created by Павел Филиппов on 24.11.2021.
//

#ifndef CLASS_CSR_MATRIX_CSR_MATRIX_H
#define CLASS_CSR_MATRIX_CSR_MATRIX_H

#include <iostream>
#include <vector>
#include "cmath"
using namespace std;

namespace csrMatrix
{

    template<typename T>
    class csrMatrix
    {
    public:

        // === CREATION ==============================================

        explicit csrMatrix(int n); // square matrix n×n
        csrMatrix(int rows1, int columns1); // general matrix
        ~csrMatrix();


        // === GETTERS / SETTERS ==============================================

        int getRowCount() const;
        int getColumnCount() const;


        // === VALUES ==============================================

        T get(int row, int col) const;
        csrMatrix & set(T val, int row, int col);


        // === OPERATIONS ==============================================

        vector<T> multiply(const vector<T> & x) const;
        vector<T> operator * (const vector<T> & x) const;

        csrMatrix<T> multiply(const csrMatrix<T> & m1) const;
        csrMatrix<T> operator * (const csrMatrix<T> & m2) const;


        // === FRIEND FUNCTIONS =========================================

        template<typename X>
        friend std::ostream & operator << (std::ostream & os, const csrMatrix<X> & matrix);


    protected:

        int m{}, n{};

        vector<T> * vals;
        vector<int> * rows{}, * cols{};


        // === HELPERS / VALIDATORS ==============================================

        void construct(int m, int n);
        void destruct();
		void validateCoordinates(int row, int col) const;
        void insert(int index, int row, int col, T val);
        void remove(int index, int row);

    };
}
#endif //CLASS_CSR_MATRIX_CSR_MATRIX_H
