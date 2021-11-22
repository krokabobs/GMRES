#include <vector>
#include <iostream>
using namespace std;
int main()
{
    vector <double> sparseMatrix = { 0, 0, 0, 5, 0, 2, 0, 0, 1, 3, 0, 0, 0, 0, 4, 0};
    int N = 4;
    auto s = sparseMatrix.data();
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
    return 0;
}