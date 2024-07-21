// метод Гауса-Зейделя.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include<omp.h>
#include<math.h>
using namespace std;

int main(int arge, char** argv)
{
    setlocale(LC_ALL, "Russian");
    int matrixsizes[] = { 100, 250, 500 };
    double tn, tk, deltat, tmp;

    for (int N : matrixsizes) {
        double** matrixA = new double* [N];   
        double* matrixB = new double[N];
        double* matrixX = new double[N];


        for (int i = 0; i < N; i++) {
            matrixA[i] = new double[N];
        }

        char filenameA[50];      
        char filenameB[50];
        char filenameX[50];

        sprintf_s(filenameA, "matrixA%d.txt", N);
        sprintf_s(filenameB, "matrixB%d.txt", N);
        sprintf_s(filenameX, "matrixXt%d.txt", N);

        ifstream matrA(filenameA);
        ifstream matrB(filenameB);
        ofstream matrX(filenameX);


        if (!matrA.is_open() || !matrB.is_open()) {   
            printf_s("Не удалось открыть файл!");
            return 1;
        }

        for (int i = 0; i < N; i++) {                 
            for (int j = 0; j < N; j++) {
                matrA >> matrixA[i][j];
            }
            matrB >> matrixB[i];
            matrixX[i] = 1.0;
        }

        double xmax = -1.0, eps = 0.0001, sum1, sum2, tmp;  

        tn = omp_get_wtime();

        do {
            xmax = -1.0;
            for (int i = 0; i < N; i++) {
                tmp = matrixX[i];
                sum1 = 0.0; sum2 = 0.0;
                for (int j = 0; j < i ; j++) {
                    sum1 += matrixA[i][j] * matrixX[j];
                }
                for (int j = i + 1; j < N; j++) {
                    sum2 += matrixA[i][j] * matrixX[j];
                }
                matrixX[i] = 1.0 / matrixA[i][i] * (matrixB[i] - sum1 - sum2);
                double  tmp = fabs(matrixX[i] - tmp);
                if (tmp > xmax) {
                    xmax = tmp;
                }
            }
        } while (xmax > eps);

        tk = omp_get_wtime();

        for (int i = 0; i < N; i++) {
            matrX << matrixX[i] << endl;
        }
        matrA.close();
        matrB.close();
        matrX.close();
        delete[] matrixA;
        delete[] matrixB;
        delete[] matrixX;
        double deltaT = tk - tn;
        printf("%8.8f \n", deltaT);
    }

    return 0;

}
