#include "hw1.h"

Matrix algebra::zeros(size_t n, size_t m)
{
    return Matrix(n, std::vector<double>(m, 0.0));
}

Matrix algebra::ones(size_t n, size_t m)
{
    return Matrix(n, std::vector<double>(m, 1.0));
}


Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    if(min > max)
    {
        throw std::logic_error("min is greater than max");
    }

    Matrix matrix(n, std::vector<double>(m, 0.0));
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(min, max);

    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < m; ++j)
        {
            matrix[i][j] = distribution(generator);
        }
    }

    return matrix;
}

void algebra::show(const Matrix& matrix)
{
    if(matrix.empty()) return;

    for(const std::vector<double> &row: matrix)
    {
        for(const double element: row)
        {
            std::cout << std::setw(12) << std::left << element; 
        }

        std::cout << std::endl;
    }
}


Matrix algebra::multiply(const Matrix& matrix, double c)
{
    Matrix m_matrix(matrix);

    if(!m_matrix.empty())
    {
        for(std::vector<double> &row: m_matrix)
        {
            for(double &element: row)
            {
                element *= c; 
            }
        }
    }

    return m_matrix;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2)
{
    Matrix m_matrix;

    if(matrix1.empty() || matrix2.empty())
    {
        if(matrix1.empty() && matrix2.empty()) return m_matrix;
        else throw std::logic_error("A non-empty matrix cannot be multiplied with an empty matrix");
    }

    if(matrix1[0].size() == matrix2.size())
    {
        size_t n = matrix1.size();
        size_t m = matrix2[0].size();
        
        m_matrix = Matrix(n, std::vector<double>(m, 0.0));

        for(size_t i = 0; i < n; ++i)
        {
            for(size_t j = 0; j < m; ++j)
            {
                for(size_t k = 0; k < matrix2.size(); ++k)
                {
                    m_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }

        return m_matrix;
    }
    else throw std::logic_error("The number of columns of matrix1 is not equal to the number of rows of matrix2");   
}

Matrix algebra::sum(const Matrix& matrix, double c)
{
    Matrix m_matrix(matrix);

    if(!matrix.empty())
    {
        for(std::vector<double> &row: m_matrix)
        {
            for(double &element: row)
            {
                element += c; 
            }
        }

        
    }
    
    return m_matrix;
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2)
{
    Matrix m_matrix(matrix1);

    if(matrix1.empty() || matrix2.empty())
    {
        if(matrix1.empty() && matrix2.empty()) return m_matrix;
        else throw std::logic_error("A non-empty matrix cannot be added to an empty matrix");
    }

    size_t n = matrix1.size();
    size_t m = matrix1[0].size();

    if(n == matrix2.size() && m == matrix2[0].size())
    {
        for(size_t i = 0; i < n; ++i)
        {
            for(size_t j = 0; j < m; ++j)
            {
                m_matrix[i][j] += matrix2[i][j];
            }
        }

        return m_matrix;
    }
    else throw std::logic_error("The number of rows and columns of matrix1 and matrix2 are not equal");
}

Matrix algebra::transpose(const Matrix& matrix)
{
    Matrix m_matrix;

    if(!matrix.empty())
    {
        size_t n = matrix[0].size();
        size_t m = matrix.size();

        m_matrix = Matrix(n, std::vector<double>(m, 0.0));

        for(size_t i = 0; i < n; ++i)
        {
            for(size_t j = 0; j < m; ++j)
            {
                m_matrix[i][j] = matrix[j][i];
            }
        }
    }

    return m_matrix;
}

Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m)
{
    if(matrix.empty()) throw std::logic_error("matrix is an empty matrix");

    size_t row = matrix.size();
    size_t column = matrix[0].size();
    if(n >= row || m >= column) throw std::logic_error("The input n and m are wrong.");
    
    Matrix m_matrix(row - 1, std::vector<double>(column - 1, 0.0));
    for(size_t m_i = 0, i = 0; i < row; ++i)
    {
        if(i != n)
        {
            for(size_t m_j = 0, j = 0; j < column; ++j)
            {
                if(j != m)
                {
                    m_matrix[m_i][m_j] = matrix[i][j];
                    ++m_j;
                }
            }

            ++m_i;
        }
    }

    return m_matrix;
}

double algebra::determinant(const Matrix& matrix)
{
    if(matrix.empty()) return 1.0;

    if(matrix.size() != matrix[0].size()) throw std::logic_error("The matrix is not square");
    else
    {
        double value = 0.0;
        int sign = 1;
        for(size_t i = 0; i < matrix.size(); ++i)
        {
            (i % 2)? sign = -1: sign = 1;
            value += (sign * matrix[i][0] * determinant(minor(matrix, i, 0)));
        }
        return value;
    }
}

Matrix algebra::inverse(const Matrix& matrix)
{
    if(matrix.empty()) return matrix;

    if(matrix.size() != matrix[0].size())
    {
        throw std::logic_error("This matrix does not have an inverse");
    }

    double det = determinant(matrix);
    if(det == 0.0) throw std::logic_error("The determinant of this matrix is 0");

    size_t n = matrix.size();
    Matrix new_matrix(n, std::vector<double>(n, 0.0));
    int sign = 1;
    for(size_t i = 0; i < n; ++i)
    {
        for(size_t j = 0; j < n; ++j)
        {
            (i + j) % 2? sign = -1: sign = 1;
            new_matrix[i][j] = sign * determinant(minor(matrix, j, i));
        }
    }

    return multiply(new_matrix, 1 / det);
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis)
{
    if(axis != 0 && axis != 1) throw std::logic_error("Wrong axis value");

    if(matrix1.empty() || matrix2.empty())
    {
        if(matrix1.empty()) return matrix2;
        else return matrix1;
    }

    Matrix new_matrix;
    if(axis)
    {
        if(matrix1.size() != matrix2.size()) 
        {
            throw std::logic_error("The two matrices have different numbers of rows and cannot be concatenated");
        }

        size_t row = matrix1.size();
        size_t column = matrix1[0].size() + matrix2[0].size();
        new_matrix = Matrix(row, std::vector<double>(column, 0.0));

        for(size_t i = 0; i < row; ++i)
        {
            for(size_t j = 0; j < matrix1[0].size(); ++j)
            {
                new_matrix[i][j] = matrix1[i][j];
            }

            for(size_t j = 0; j < matrix2[0].size(); ++j)
            {
                new_matrix[i][j + matrix1[0].size()] = matrix2[i][j];
            }
        }
    }
    else
    {
        if(matrix1[0].size() != matrix2[0].size()) 
        {
            throw std::logic_error("The two matrices have different numbers of column and cannot be concatenated");
        }

        size_t row = matrix1.size() + matrix2.size();
        size_t column = matrix1[0].size();
        new_matrix = Matrix(row, std::vector<double>(column, 0.0));

        for(size_t j = 0; j < column; ++j)
        {
            for(size_t i = 0; i < matrix1.size(); ++i)
            {
                new_matrix[i][j] = matrix1[i][j];
            }

            for(size_t i = 0; i < matrix2.size(); ++i)
            {
                new_matrix[i + matrix1.size()][j] = matrix2[i][j];
            }
        }
    }

    return new_matrix;
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2)
{
    if(r1 >= matrix.size() || r2 >= matrix.size())
    {
        throw std::logic_error("r1 or r2 out of range");
    }

    if(matrix.empty()) return matrix;

    Matrix new_matrix(matrix);

    for(size_t j = 0; j < matrix[0].size(); ++j)
    {
        std::swap(new_matrix[r1][j], new_matrix[r2][j]);
    }

    return new_matrix;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c)
{
    if(matrix.empty()) return matrix;

    if(r >= matrix.size())
    {
        throw std::logic_error("r out of range");
    }

    Matrix new_matrix(matrix);

    for(size_t j = 0; j < matrix[0].size(); ++j)
    {
        new_matrix[r][j] *= c;
    }

    return new_matrix;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
{
    if(matrix.empty()) return matrix;

    if(r1 >= matrix.size() || r2 >= matrix.size())
    {
        throw std::logic_error("r1 or r2 out of range");
    }

    Matrix new_matrix(matrix);
    for(size_t j = 0; j < matrix[0].size(); ++j)
    {
        new_matrix[r2][j] += (matrix[r1][j] * c);
    }
    return new_matrix;
}

Matrix algebra::upper_triangular(const Matrix& matrix)
{
    if(matrix.empty()) return matrix;

    if(matrix.size() != matrix[0].size()) throw std::logic_error("The matrix is not square");
    
    Matrix new_matrix(matrix);
    size_t n = matrix.size();
    for(size_t i = 0; i < n; ++i) // Handling the case where there are 0 on the main diagonal
    {
        if(new_matrix[i][i] == 0)
        {
            size_t n_i = i + 1;
            while(n_i < n && new_matrix[n_i][n_i] == 0) ++n_i;

            if(n_i < n)
            {
                new_matrix = ero_swap(new_matrix, i, n_i);
            }
        }
    }

    double c;
    for(size_t i = 0; i < n; ++i)
    {
        for(size_t n_i = i + 1; n_i < n; ++n_i)
        {
            c = -(new_matrix[n_i][i] / new_matrix[i][i]);
            new_matrix = ero_sum(new_matrix, i, c, n_i);
        }
    }

    return new_matrix;
}