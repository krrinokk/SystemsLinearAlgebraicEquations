// метод Гаусса.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include<omp.h>
#include<math.h>
using namespace std;
int main(int arge, char** argv)
{
	int matrixsizes[] = { 100, 250, 500 };

	double xmax = -1.0;
	double eps = 0.0001;
	double sum1, sum2, sum;
	for (int N : matrixsizes) {
		double** matrixA = new double* [N];
		double* matrixB = new double[N];
		double* matrixX = new double[N];
		double* matrixXX = new double[N];

		for (int i = 0; i < N; i++) {
			matrixA[i] = new double[N];
		}
		char filenameA[5000];
		char filenameB[5000];
		char filenameX[5000];
		sprintf_s(filenameA, "matrixA%d.txt", N);
		sprintf_s(filenameB, "matrixB%d.txt", N);
		sprintf_s(filenameX, "matrixX%d.txt", N);
		ifstream matrA(filenameA);
		ifstream matrB(filenameB);
		ofstream matrX(filenameX);
		if (!matrA.is_open() || !matrB.is_open()) {
			return 1;
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrA >> matrixA[i][j];
			}
			matrB >> matrixB[i];
			matrixX[i] = matrixXX[i] = 0.0;
		}
		double xmax = -1.0, eps = 0.0001, tn, tk, deltat, tmp;
		tn = omp_get_wtime();
		//прямой ход 
		double* w = new double [N];
		for (int i = 1; i < N; i++) {
			int l = i - 1;
			for (int j = 0; j < N - 1; j++) {
				w[j] = -matrixA[j + 1][l] / matrixA[l][l];
			}
				for (int k = i; k < N; k++) {
					for (int j = 0; j < N; j++) {
						matrixA[k][j] += matrixA[l][j] * w[k - i];
					}
						matrixB[k] += matrixB[l] * w[k - i];
					
				
			}
		}

			//обратный ход
			double sum ;
			for (int j = N-1 ; j >= 0; j--) {
				sum = 0.0;
				for (int i = j; i < N-1; i++) {
					sum += matrixA[j][i + 1] * matrixX[i + 1];
				}
					matrixX[j] = (matrixB[j] - sum) / matrixA[j][j];
				
			}
			tk = omp_get_wtime();
			for (int i = 0; i < N; i++) matrX << matrixX[i] << endl;

			matrA.close();
			matrB.close();
			matrX.close();
			delete[] matrixA;
			delete[] matrixB;
			delete[] matrixX;
			delete[] matrixXX;
			double deltaT = tk - tn;
			printf("%8.8f \n", deltaT);
		}
		return 0;
	
}
