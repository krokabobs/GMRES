//
// Created by Павел Филиппов on 24.11.2021.
//

#include "csr_matrix.h"
#include <vector>
#include <iostream>

namespace csrMatrix
{
	template class csrMatrix<int>;

    template<typename T>
    csrMatrix<T>::csrMatrix(int n)
    {
        this->construct(n, n);
    }

    template<typename T>
    csrMatrix<T>::csrMatrix(int rows, int columns)
    {
        this->construct(rows, columns);
    }


    template<typename T>
    csrMatrix<T>::~csrMatrix()
    {
        this->destruct();
    }


    template<typename T>
    void csrMatrix<T>::construct(int rows1, int columns1)
    {
        this->m = rows1;
        this->n = columns1;

        this->vals = NULL;
        this->cols = NULL;
        this->rows = new vector<int>(rows1 + 1, 1);
    }


    template<typename T>
    void csrMatrix<T>::destruct()
    {
        if (this->vals != NULL) {
            delete this->vals;
            delete this->cols;
        }

        delete this->rows;
    }


    // === GETTERS / SETTERS ==============================================

    template<typename T>
    int csrMatrix<T>::getRowCount() const
    {
        return this->m;
    }


    template<typename T>
    int csrMatrix<T>::getColumnCount() const
    {
        return this->n;
    }


    // === VALUES ==============================================

    template<typename T>
    T csrMatrix<T>::get(int row, int col) const
    {

        int currCol;

        for (int pos = (*(this->rows))[row - 1] - 1; pos < (*(this->rows))[row] - 1; ++pos) {
            currCol = (*(this->cols))[pos];

            if (currCol == col) {
                return (*(this->vals))[pos];

            } else if (currCol > col) {
                break;
            }
        }

        return T();
    }


    template<typename T>
    csrMatrix<T> & csrMatrix<T>::set(T val, int row, int col)
    {

        int pos = (*(this->rows))[row - 1] - 1;
        int currCol = 0;

        for (; pos < (*(this->rows))[row] - 1; pos++) {
            currCol = (*(this->cols))[pos];

            if (currCol >= col) {
                break;
            }
        }

        if (currCol != col) {
            if (!(val == T())) {
                this->insert(pos, row, col, val);
            }

        } else if (val == T()) {
            this->remove(pos, row);

        } else {
            (*(this->vals))[pos] = val;
        }

        return *this;
    }


    // === OPERATIONS ==============================================

    template<typename T>
    vector<T> csrMatrix<T>::multiply(const vector<T> & x) const
    {
        vector<T> result(this->m, T());

        if (this->vals != NULL) { // only if any value set
            for (int i = 0; i < this->m; i++) {
                T sum = T();
                for (int j = (*(this->rows))[i]; j < (*(this->rows))[i + 1]; j++) {
                    sum = sum + (*(this->vals))[j - 1] * x[(*(this->cols))[j - 1] - 1];
                }

                result[i] = sum;
            }
        }

        return result;
    }


    template<typename T>
    vector<T> csrMatrix<T>::operator * (const vector<T> & x) const
    {
        return this->multiply(x);
    }


    template<typename T>
    csrMatrix<T> csrMatrix<T>::multiply(const csrMatrix<T> & m1) const
    {
        csrMatrix<T> result(this->m, m1.n);
        T a;
        for (int i = 1; i <= this->m; i++) {
            for (int j = 1; j <= m1.n; j++) {
                a = T();

                for (int k = 1; k <= this->n; k++) {
                    a = a + this->get(i, k) * m1.get(k, j);
                }

                result.set(a, i, j);
            }
        }

        return result;
    }


    template<typename T>
    csrMatrix<T> csrMatrix<T>::operator * (const csrMatrix<T> & m2) const
    {
        return this->multiply(m2);
    }


    // === HELPERS / VALIDATORS ==============================================


    template<typename T>
    void csrMatrix<T>::insert(int index, int row, int col, T val)
    {
        if (this->vals == NULL) {
            this->vals = new vector<T>(1, val);
            this->cols = new vector<int>(1, col);

        } else {
            this->vals->insert(this->vals->begin() + index, val);
            this->cols->insert(this->cols->begin() + index, col);
        }

        for (int i = row; i <= this->m; i++) {
            (*(this->rows))[i] += 1;
        }
    }


    template<typename T>
    void csrMatrix<T>::remove(int index, int row)
    {
        this->vals->erase(this->vals->begin() + index);
        this->cols->erase(this->cols->begin() + index);

        for (int i = row; i <= this->m; i++) {
            (*(this->rows))[i] -= 1;
        }
    }


    // === FRIEND FUNCTIONS =========================================


    template<typename T>
    std::ostream & operator << (std::ostream & os, const csrMatrix<T> & matrix)
    {
        for (int i = 1; i <= matrix.m; i++) {
            for (int j = 1; j <= matrix.n; j++) {
                if (j != 1) {
                    os << " ";
                }

                os << matrix.get(i, j);
            }

            if (i < matrix.m) {
                os << std::endl;
            }
        }

        return os;
    }

}
/*
void csrMatrix::MtxToCSR(vector<double>&mtx)
{
    int N = sqrt(mtx.size());
    auto s = mtx.data();
    int size = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s[i * N + j] != 0)
                size++;
    vector<double>compactMatrix(3*size);
    auto c = compactMatrix.data();
    int k = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (s[i*N+j] != 0)
            {
                c[k] = i;
                c[1*size + k] = j;
                c[2*size + k] = s[i*N+j];
                k++;
            }
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<size; j++)
            cout << c[i*size + j] << ' ';
        cout << "\n";
    }

}
*/