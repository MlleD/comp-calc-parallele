#include "matrix.hpp"
#include "multseqmatrix.hpp"

matrix_t multiplySEQ(matrix_t matrixOne, matrix_t matrixTwo)
{
    int width1 = matrixOne[0].size();
    if (width1 != matrixTwo.size())
    {
        return matrix_t(0);
    }
    int height = matrixOne.size();
    int width2 = matrixTwo[0].size();
    matrix_t result(height, std::vector<int>(width2, 0));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width2; j++)
        {
            for (int k = 0; k < width1; k++)
            {
                result[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
    return result;
}
