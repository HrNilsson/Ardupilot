
#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

//typedef float matrix[][];
typedef float matrix3_3[3][3];
typedef float matrix120_3[120][3];
typedef float matrix120_6[120][6];
typedef float matrix120_120[120][120];

struct matrixx3_3
{
    float matrix3_3[3][3];
    uint16_t rDim = 3;
    uint16_t cDim = 3;
};

template <typename T>
class Matrix {
public:

    //float matrix [3][3];
    // matrix3_3 matrix;

    /*float **ptr;
    ptr = new float *[3];
    for(int i = 0; i<3; ++i)
        ptr[i] = new float[3];

    float testArr[3][3] = { {0} };

   testArr =  Matrix::add(testArr, testArr);

   //ptr = testArr;
   // float** ptr;

   // ptr = &testArr;

    Matrix test(3,3,ptr);

    test = Matrix::matrixAddition(test,test);*/
    T matrix;

    // Constructor
    Matrix<T>()
    {
        //T matrix;

        for(int i=0; i<matrix.rDim; ++i)
        for(int j=0; j<matrix.cDim; ++j)
        {
            matrix[i][j] = 0;
        }
    }

     const Matrix<T> operator=(const Matrix<T> &m) const
    {
       return m;
    }

   /*const Matrix<T> & operator()(uint8_t i, uint8_t j) const
    {
        const Matrix<T> *_v = &matrix;
        return _v[i][j];
    }*/

    /*const Matrix<T> & operator[](uint8_t i) const
    {
        const Matrix<T> *_v = &matrix;
        return _v[i];
    }*/

        class CRow {
            friend class Matrix;
        public:
            int& operator[](int col)
            {
                return parent.matrix[row][col];
            }
        private:
            CRow(Matrix &parent_, int row_) :
                parent(parent_),
                row(row_)
            {}

            Matrix& parent;
            int row;
        };

        CRow operator[](int row)
        {
            return CRow(*this, row);
        }

    // addition
    Matrix<T> operator        + (const Matrix<T> &m) const
    {
        for(int i=0; i<matrix.rDim; ++i)
        for(int j=0; j<matrix.cDim; ++j)
        {
            matrix[i][j] = matrix[i][j] + m[i][j];
        }

        return matrix;
    }

    // subtraction
    Matrix operator        - (const Matrix &m) const
    {
        for(int i=0; i<matrix.rDim; ++i)
        for(int j=0; j<matrix.cDim; ++j)
        {
            matrix[i][j] = matrix[i][j] - m[i][j];
        }

        return matrix;
    }

    // matrix multiplication
    Matrix operator        * (const Matrix &m) const
    {
        for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
        for(int k=0; k<3; ++k)
        {
            matrix[i][j]+= matrix[i][k]*m[k][j];
        }

        return matrix;
    }
/*
    static void add(matrix3_3* A, matrix3_3* B, matrix3_3* res);
    static matrix3_3* subtract(matrix3_3* A, matrix3_3* B);
    static matrix3_3* multiply(matrix3_3* A, matrix3_3* B);
    static matrix3_3* multiplyScalar(matrix3_3* A, float i);
    static matrix3_3* transpose(matrix3_3* A);

    static matrix120_3 add(matrix120_3 A, matrix120_3 B);
    static matrix120_3 subtract(matrix120_3 A, matrix120_3 B);
    static matrix120_3 multiply(matrix120_3 A, matrix120_3 B);
    static matrix120_3 multiplyScalar(matrix120_3 A, int16_t i);
    static matrix120_3 transpose(matrix120_3 A);

    static matrix120_6 add(matrix120_6 A, matrix120_6 B);
    static matrix120_6 subtract(matrix120_6 A, matrix120_6 B);
    static matrix120_6 multiply(matrix120_6 A, matrix120_6 B);
    static matrix120_6 multiplyScalar(matrix120_6 A, matrix120_6 i);
    static matrix120_6 transpose(matrix120_6 A);

    static matrix120_120 add(matrix120_120 A, matrix120_120 B);
    static matrix120_120 subtract(matrix120_120 A, matrix120_120 B);
    static matrix120_120 multiply(matrix120_120 A, matrix120_120 B);
    static matrix120_120 multiplyScalar(matrix120_120 A, int16_t i);
    static matrix120_120 transpose(matrix120_120 A);*/

};

#endif // VECTOR_H
