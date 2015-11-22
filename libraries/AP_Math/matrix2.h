
#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

class Matrix {
public:

    int rows, cols;
    float **arr;

    // Constructor
    Matrix(int r, int c, float ** p)
    {
        rows = r;
        cols = c;

        arr = p;

        /*for(int i=0; i<row; ++i)
        for(int j=0; j<col; ++j)
        {
            arr[i][j] = p[i][j];
        }*/
    }

    float** Matrix::add (int a,int b,int c,int d, float A[a][b], float B[c][d])
    {
        return A;
    }


     const Matrix operator=(const Matrix &m) const
    {
       return m;
    }


        class CRow {
            friend class Matrix;
        public:
            float& operator[](int col)
            {
                return parent.arr[row][col];
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

    float** matrixAddition(float** A, float ** B)
    {
        for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
        {
            A[i][j] += B[i][j];
        }

        return A;
    }

    /*Matrix& operator        + (Matrix &m)
    {
        for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; ++j)
        {
            arr[i][j] += m[i][j];
        }

        return arr;
    }


    const Matrix<T> & operator()(uint8_t i, uint8_t j) const
     {
         const Matrix<T> *_v = &matrix;
         return _v[i][j];
     }*/

     /*const Matrix<T> & operator[](uint8_t i) const
     {
         const Matrix<T> *_v = &matrix;
         return _v[i];
     }*/

   /* // addition


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
