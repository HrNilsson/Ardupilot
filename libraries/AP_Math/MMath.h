#ifndef MMATH_H
#define MMATH_H

#include "stddef.h"
#include <stdlib.h>
#include <limits>




void Madd(double *A, double *B, size_t l, double *res);
void Madd(double **A, double **B, size_t r, size_t c, double **res);

void Msubtract(double **A, double **B, size_t r, size_t c, double **res);

void Mmultiply(double **A, double **B, size_t rA, size_t cA, size_t rB, size_t cB, double **res);

void MmultiplyScalar(double **A, size_t r, size_t c, double s, double **res);

void Mtranspose(double **A, size_t rA, size_t cA, double **res);

bool compareM(float A[][2], float B[][2], size_t r, size_t c);
bool compareM(float A[][3], float B[][3], size_t r, size_t c);
bool compareM(float A[][4], float B[][4], size_t r, size_t c);
bool compareM(float A[][5], float B[][5], size_t r, size_t c);


void populateArray(float **p, size_t rows, size_t cols, float ar[3][3]);

float** ptrAlloc(size_t rows, size_t cols);

double** ptrAlloc(size_t rows, size_t cols, double ar[][1]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][2]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][3]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][4]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][5]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][6]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][50]);
double** ptrAlloc(size_t rows, size_t cols, double ar[][90]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);

#endif // MMATH_H
