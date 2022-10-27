#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "signal.h"

#define pi 3.142857 //Pi
#define N 512	// Signal Length
#define L 32		// DCT Size
#define M 8	// DCT Coeff

float dct[L][L];	// DCT Matrix
float y[M][N / L];	// Transmission data

void create_dctMatrix() {
	float sc = 0;

	for (int k = 0; k < L; k++) {
		for (int n = 0; n < L; n++) {
			if (k == 0) {
				sc = 1 / sqrt(L);
			}
			else {
				sc = sqrt(2) / sqrt(L);
			}
			dct[k][n] = sc*(cos((pi / L)*(n + 0.5)*k));
			printf("%.4f ", dct[k][n]);
		}
		printf("\n");
	}
}

void dct_Transform() {
	float tmp = 0; //Temporary
	int c = 0; //Counter - For padding
	for (int i = 0; i < N / L; i++) { //Matrix multiplication
		for (int j = 0; j < M; j++) { //M = DCT Coefficients	
			for (int t = 0; t < L; t++) {
				tmp = tmp + dct[j][t] * x[t+(c*L)]; //If using prestored dct use dct8 or dct16
			}
			y[j][i] = tmp;
			tmp = 0;
		}
		c = c + 1;
	}
}

void print_Matrix() {
	printf("[");
	for (int i = 0; i < N / L; i++) {
		for (int j = 0; j <  M; j++) {
			printf("%.4f ", y[j][i]);
		}
		printf("\n");
	}
	printf("]\n");
}


int main(void)
{
	int p = 0;
	printf("Hello World!\n");

	//printf("Signal:\n");
	//for (int u = 0; u < N; u++) {
		
		//printf("%.4f ", x[u]);
	//	if (p == 8) { printf("\n"); }
	//}

	create_dctMatrix();
	printf("Created DCT\n");
	dct_Transform();
	printf("Transformed\n");
	print_Matrix();


	return 0;
}
