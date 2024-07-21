// Генерация матриц.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <omp.h>
#include <cmath>

#include <cstdlib>
#include <ctime>
using namespace std;
int main(int arge, char **argv)
{
	
	double tn;
	setlocale(0, "Russian");
	char filenameA[256];
	char filenameB[256];
	int matrixsizes[] = { 100, 250, 500 };

	

	for (int N : matrixsizes) {
		sprintf_s(filenameA, "matrixA%d.txt", N);
		sprintf_s(filenameB, "matrixB%d.txt", N);
		ofstream matrixA(filenameA);
		ofstream matrixB(filenameB);
		if (!matrixA.is_open() || !matrixB.is_open()) {
			cout << "error . write to file." << endl;
			return 1;
		}
		double* matrA = new double[N];
		double* matrB = new double[N];
		for (int i = 0; i < N; i++) {
			double sum = 0.0;
			for (int j = 0; j < N; j++) {
				matrA[j] = rand() % 10;
			
				sum += matrA[j];
			}
			matrA[i] = sum + 1.0;
			for (int j = 0; j < N; j++) {
				matrixA << matrA[j] << "\t";
			}
			matrixA << endl;
			matrB[i] = rand() % 10;
		
			matrixB << matrB[i] << "\t";
		}
		matrixA.close();
		matrixB.close();
	

	}
	
	return 0;


		
}

 