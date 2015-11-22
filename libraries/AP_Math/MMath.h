#ifndef MMATH_H
#define MMATH_H

#include "stddef.h"
#include <stdlib.h>
#include <limits>




void Madd(float **A, float **B, size_t r, size_t c, float **res);

void Msubtract(float **A, float **B, size_t r, size_t c, float **res);

void Mmultiply(float **A, float **B, size_t rA, size_t cA, size_t rB, size_t cB, float **res);

void MmultiplyScalar(float **A, size_t r, size_t c, float s, float **res);

void Mtranspose(float **A, size_t rA, size_t cA, float **res);

bool compareM(float A[][2], float B[][2], size_t r, size_t c);
bool compareM(float A[][3], float B[][3], size_t r, size_t c);
bool compareM(float A[][4], float B[][4], size_t r, size_t c);
bool compareM(float A[][5], float B[][5], size_t r, size_t c);


void populateArray(float **p, size_t rows, size_t cols, float ar[3][3]);

float** ptrAlloc(size_t rows, size_t cols);

float** ptrAlloc(size_t rows, size_t cols, float ar[][2]);
float** ptrAlloc(size_t rows, size_t cols, float ar[][3]);
float** ptrAlloc(size_t rows, size_t cols, float ar[][4]);
float** ptrAlloc(size_t rows, size_t cols, float ar[][5]);
float** ptrAlloc(size_t rows, size_t cols, float ar[][50]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);
//float** ptrAlloc(size_t rows, size_t cols, float ar[3][3]);

#endif // MMATH_H
