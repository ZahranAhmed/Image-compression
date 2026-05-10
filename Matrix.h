// ============================
// MATRIX.H
// ============================

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <typename T>
class Matrix
{
private:

    int rows;
    int cols;
    T** data; // it creates a 2D dynamic array e.g: data[row][column]

public:

    // Constructor
    Matrix(int r = 0, int c = 0)
    {
        rows = r;
        cols = c;

        if (rows <= 0 || cols <= 0)
        {
            data = nullptr;
            return;
        }

        data = new T * [rows]; // allocatiing new memory by by creating fresh row pointers

        for (int i = 0; i < rows; i++)
        {
            data[i] = new T[cols];
        }
    }

    // Copy Constructor
    Matrix(const Matrix& other)
    {
        rows = other.rows;
        cols = other.cols;

        if (rows <= 0 || cols <= 0)
        {
            data = nullptr;
            return;
        }

        data = new T * [rows];

        for (int i = 0; i < rows; i++)
        {
            data[i] = new T[cols];

            for (int j = 0; j < cols; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Copy Assignment Operator
    Matrix& operator=(const Matrix& other)
    {
        if (this != &other)
        {
            // Delete old memory
            if (data != nullptr)
            {
                for (int i = 0; i < rows; i++)
                {
                    delete[] data[i];
                }

                delete[] data;
            }

            // Copy size
            rows = other.rows;
            cols = other.cols;

            if (rows <= 0 || cols <= 0)
            {
                data = nullptr;
                return *this;
            }

            // Allocate new memory
            data = new T * [rows];

            for (int i = 0; i < rows; i++)
            {
                data[i] = new T[cols];

                for (int j = 0; j < cols; j++)
                {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        return *this;
    }

    // Destructor
    ~Matrix()
    {
        if (data != nullptr)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] data[i];
            }

            delete[] data;
        }
    }

    // Access Operator
    T& operator()(int i, int j)  // overloading operator '()' so that we can wirte matrix (1,2) instead of writing matrix.data[1][2]
    {
        return data[i][j];
    }

    int getRows() const
    {
        return rows;
    }

    int getCols() const
    {
        return cols;
    }

    // Matrix Addition
    Matrix operator+(const Matrix& other)
    {
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result(i, j) =
                    data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Matrix Transpose
    Matrix transpose()
    {
        Matrix result(cols, rows);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result(j, i) = data[i][j];
            }
        }

        return result;
    }
};

#endif