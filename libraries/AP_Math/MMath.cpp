#include "MMath.h"

#pragma GCC optimize("O3")



void Madd(double **A, double **B, size_t r, size_t c, double **res)
{
    for(int i=0; i<(int)r; ++i)
    for(int j=0; j<(int)c; ++j)
    {
        res[i][j] = A[i][j] + B[i][j];
    }
}

void Madd(double *A, double *B, size_t l, double *res)
{
	for (int i = 0; i<(int)l; ++i)
		res[i] = A[i] + B[i];
}

void Msubtract(double **A, double **B, size_t r, size_t c, double **res)
{
	for (int i = 0; i<(int)r; ++i)
	for (int j = 0; j<(int)c; ++j)
	{
		res[i][j] = A[i][j] - B[i][j];
	}
}

void Mmultiply(double **A, double **B, size_t rA, size_t cA, size_t rB, size_t cB, double **res)
{
    for(int i=0; i<(int)rA; ++i) // For every row in the lhs matrix
    for(int j=0; j<(int)cB; ++j) // For every column in the rhs matrix
    for(int k=0; k<(int)cA; ++k) // Compute the sum of the products
    {
        res[i][j]+= A[i][k]*B[k][j];
    }
}

void MmultiplyScalar(double **A, size_t r, size_t c, double s, double **res)
{
    for(int i = 0; i<(int)r; ++i)
    for(int j = 0; j<(int)c; ++j)
        res[i][j] = s*A[i][j];
}

void Mtranspose(double **A, size_t r, size_t c, double **res)
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


double** ptrAlloc(size_t rows, size_t cols, double ar[][1])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][2])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][3])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][4])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}


double** ptrAlloc(size_t rows, size_t cols, double ar[][5])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][6])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][50])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}

double** ptrAlloc(size_t rows, size_t cols, double ar[][90])
{
	double **p;
	p = new double *[rows];
	for (int i = 0; i<(int)rows; ++i)
		p[i] = ar[i];

	return p;
}


