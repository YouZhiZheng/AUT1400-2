#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <utility>

// The role of using here is the same as typedef in C language
using Matrix = std::vector<std::vector<double>>;

class algebra
{
    // NOTE: Because of unit_test, the member functions here must be declared as static before they can be called
public:
    static Matrix zeros(size_t n, size_t m);
    static Matrix ones(size_t n, size_t m);
    // NOTE:Use the random library to implement
    static Matrix random(size_t n, size_t m, double min, double max);
    // NOTE:Use the iomanip library to implement
    static void show(const Matrix& matrix);
    static Matrix multiply(const Matrix& matrix, double c);
    static Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
    // NOTE:Add c to each element in the matrix
    static Matrix sum(const Matrix& matrix, double c);
    static Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    static Matrix transpose(const Matrix& matrix);
    static Matrix minor(const Matrix& matrix, size_t n, size_t m);
    static double determinant(const Matrix& matrix);
    static Matrix inverse(const Matrix& matrix);
    // NOTE:axis=0: on top of each other | axis=1: alongside each other
    static Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);

    // INFO:The following are the basic line operations
    static Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    static Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    static Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);

    static Matrix upper_triangular(const Matrix& matrix);
    
};

#endif //AP_HW1_H
