#include <iostream>
#include "cmath"

using namespace std;

void MatrVekt(int N, double **M, const double *V, double *R)
//N - размерность, M - матрица, V - вектор, R - результат
{
    for(int i=0; i<N; i++)
    {
        R[i]=0;
        for(int j=0; j<N; j++)
            R[i]+= M[i][j]*V[j];
    }
}
int MinNev(int N, double **A, const double *F, double *X, double eps)
//N - размерность, A - матрица, F - вектор свободных членов, X -вектор результат, eps- точность
{
    int count=0;//  количество итераций
    auto *R = new double [N];
    auto *Delta = new double [N];
    auto *TempX = new double[N];
    double maxi=0.0, Tau=0.0, TempTau=0.0;
    for (int i = 0; i < N; i++)
        TempX[i]=0;//первое приближение задаём нулевым
    do
    {
        MatrVekt(N, A, TempX, R);
        for(int i = 0; i < N; i++)
        {
            Delta[i]=R[i]-F[i];//Вектор невязок
        }
        MatrVekt(N, A, Delta, R);
        Tau=0.0;
        TempTau=0.0;
        for(int i=0; i<N; i++)
        {
            Tau+=R[i]*Delta[i];
            TempTau+=R[i]*R[i];
        }
        Tau=Tau/TempTau;
        for(int i=0; i<N; i++)
            X[i]=TempX[i]-Tau*Delta[i];
        maxi = abs(X[0] - TempX[0]);
        for(int i=0; i<N; i++)
        {
            if(abs(X[i]-TempX[i])>maxi)
                maxi=abs(X[i]-TempX[i]);
            TempX[i]=X[i];
        }
        count++;
    }
    while (maxi>=eps);
    delete[] R;
    delete[] Delta;
    delete[] TempX;
    return count;
}
int main()
{
    int N=3;
    float eps = 0.001;
    double **A;
    A = new double *[N];
    for(int i = 0; i < N; i++)
        A[i]= new double [N];

    A[0][0]= 2;A[0][1]= 4;A[0][2]= -6;
    A[1][0]= 6;A[1][1]= -4;A[1][2]= 2;
    A[2][0]= 4;A[2][1]= 2;A[2][2]= 6;
    double F[3]={ 4, 4, 8 };
    double R[3];
    MatrVekt(N,A,F,R);
    cout << "Результирующий вектор:\n";
    for (int i = 0; i < N; i++){
    cout << R[i] << '\n';
    }
    cout << "Количество итераций:\n";
    cout << MinNev(N, A, F, R, eps);
    delete[] A;
    return 0;
}