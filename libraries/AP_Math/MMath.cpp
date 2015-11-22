#include "MMath.h"

#pragma GCC optimize("O3")



void Madd(float **A, float **B, size_t r, size_t c, float **res)
{
    for(int i=0; i<(int)r; ++i)
    for(int j=0; j<(int)c; ++j)
    {
        res[i][j] = A[i][j] + B[i][j];
    }
}

void Msubtract(float **A, float **B, size_t r, size_t c, float **res)
{
	for (int i = 0; i<(int)r; ++i)
	for (int j = 0; j<(int)c; ++j)
	{
		res[i][j] = A[i][j] - B[i][j];
	}
}

void Mmultiply(float **A, float **B, size_t rA, size_t cA, size_t rB, size_t cB, float **res)
{
    for(int i=0; i<(int)rA; ++i) // For every row in the lhs matrix
    for(int j=0; j<(int)cB; ++j) // For every column in the rhs matrix
    for(int k=0; k<(int)cA; ++k) // Compute the sum of the products
    {
        res[i][j]+= A[i][k]*B[k][j];
    }
}

void MmultiplyScalar(float **A, size_t r, size_t c, float s, float **res)
{
    for(int i = 0; i<(int)r; ++i)
    for(int j = 0; j<(int)c; ++j)
        res[i][j] = s*A[i][j];
}

void Mtranspose(float **A, size_t r, size_t c, float **res)
{
    for(int i = 0; i<(int)c; ++i)
    for(int j = 0; j<(int)r; ++j)
        res[i][j] = A[j][i];
}

bool compareM(float A[][2], float B[][2], size_t r, size_t c)
{
	for (int i = 0; i<(int)r; ++i)
		for (int j = 0; j<(int)c; ++j)
		{
			if (abs(A[i][j] - B[i][j]) >= std::numeric_limits<float>::epsilon())
				return false;
		}

	return true;
}


bool compareM(float A[][3], float B[][3], size_t r, size_t c)
{
	for (int i = 0; i<(int)r; ++i)
	for (int j = 0; j<(int)c; ++j)
	{
		if (abs(A[i][j] - B[i][j]) >= std::numeric_limits<float>::epsilon())
			return false;
	}

	return true;
}

bool compareM(float A[][4], float B[][4], size_t r, size_t c)
{
	for (int i = 0; i<(int)r; ++i)
		for (int j = 0; j<(int)c; ++j)
		{
			if (abs(A[i][j] - B[i][j]) >= std::numeric_limits<float>::epsilon())
				return false;
		}

	return true;
}

bool compareM(float A[][5], float B[][5], size_t r, size_t c)
{
	for (int i = 0; i<(int)r; ++i)
		for (int j = 0; j<(int)c; ++j)
		{
			if (abs(A[i][j] - B[i][j]) >= std::numeric_limits<float>::epsilon())
				return false;
		}

	return true;
}

void populateArray(float **p, size_t rows, size_t cols, float ar[3][3])
{
	for (int i = 0; i < (int)rows; ++i)
		for (int j = 0; j < (int)cols; ++j)
			ar[i][j] = p[i][j];
}

float** ptrAlloc(size_t rows, size_t cols)
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = new float[cols];

	return p;
}

float** ptrAlloc(size_t rows, size_t cols, float ar[][2])
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

float** ptrAlloc(size_t rows, size_t cols, float ar[][3])
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

float** ptrAlloc(size_t rows, size_t cols, float ar[][4])
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}


float** ptrAlloc(size_t rows, size_t cols, float ar[][5])
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

float** ptrAlloc(size_t rows, size_t cols, float ar[][50])
{
	float **p;
	p = new float *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}
