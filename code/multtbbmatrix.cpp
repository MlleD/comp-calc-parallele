#include "multtbbmatrix.hpp"
#include <iostream>
#include <tbb/tbb.h>

matrix_t multiplyTBB(matrix_t matrixOne, matrix_t matrixTwo)
{
    int width1 = matrixOne[0].size();
    if (width1 != matrixTwo.size())
    {
        return matrix_t(0);
    }

    int height = matrixOne.size();
    int width2 = matrixTwo[0].size();
    matrix_t result(height, std::vector<int>(width2, 0));

    size_t grain_size = height / 10;
    tbb::parallel_for(
        tbb::blocked_range<int>(0, height, grain_size), [&](const tbb::blocked_range<int> &range) {
            for (int i = range.begin(); i < range.end(); ++i)
            {
                for (int j = 0; j < width2; j++)
                {
                    int sum = 0;

                    for (int k = 0; k < width1; k++)
                    {
                        sum += matrixOne[i][k] * matrixTwo[k][j];
                    }
                    result[i][j] += sum;
                }
            }
        });

    return result;
}
