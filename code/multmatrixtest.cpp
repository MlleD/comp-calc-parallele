#include <iostream>
#include <string>
#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "matrix.hpp"
#endif
#include "multseqmatrix.hpp"
#include "multompmatrix.hpp"
#include "multcilkmatrix.hpp"
#include "multtbbmatrix.hpp"

bool assertEquals (matrix_t actual, matrix_t expected)
{
    bool hasError = false;
    int height = expected.size();
    if (actual.size() != height)
    {
        std::cout << "Not same number of rows. Expected " << height;
        std::cout << " but got " << actual.size() << "." << std::endl;
        return true;
    }
    for (int i = 0; i < height; i++)
    {
        int width = expected[i].size();
        if (actual[i].size() != width)
        {
            std::cout << "Not same number of columns for row " + std::to_string(i) << ". ";
            std::cout << "Expected " << width << " but got " << actual[i].size() << "." << std::endl;
            return true;
        }
        for (int j = 0; j < width; j++)
        {
            if (actual[i][j] != expected[i][j])
            {
                std::cout << "Expected " << expected[i][j] << " but got " << actual[i][j];
                std::cout << " at row " << i << " and col " << j << std::endl;
                hasError = true;
            }
        }
    }
    return hasError;
}

int main(int argc, char const *argv[])
{
    // Tests de correction de la multiplication
    matrix_t t1 = {
        {7, 9, 10, 6, 8, 5, 11},
        {12, 17, 15, 13, 14, 18, 16},
        {2, 0, 4, -1, 3, 1, -2},
        {22, 19, 23, 20, 24, 21, 25},
        {29, 31, 26, 27, 32, 30, 28}
    };
    matrix_t t2 = {
        {52, 51, 54, 53, 50 },
        {47, 45, 46, 48, 49 },
        {44, 42, 40, 41, 43 },
        {37, 39, 35, 36, 38 },
        {56, 58, 57, 55, 59 },
        {62, 61, 60, 64, 63 },
        {66, 67, 69, 65, 68}
    };
    matrix_t expected = {
        {2933, 2922, 2917, 2904, 2984},
        {5520, 5496, 5467, 5497, 5620},
        {341, 332, 326, 333, 338},
        {8085, 8071, 8035, 8030, 8219},
        {10608, 10581, 10533, 10563, 10795}
    };
    matrix_t result = multiplySEQ(t1, t2);
    bool hasError;
    hasError = assertEquals(result, expected);
    if (!hasError) std::cout << "SEQ: Same matrices OK" << std::endl;
    hasError = assertEquals(multiplyOMP(t1, t2), expected);
    if (!hasError) std::cout << "OMP: Same matrices OK" << std::endl;
    hasError = assertEquals(multiplyCILK(t1, t2), expected);
    if (!hasError) std::cout << "CILK: Same matrices OK" << std::endl;
    hasError = assertEquals(multiplyTBB(t1, t2), expected);
    if (!hasError) std::cout << "TBB: Same matrices OK" << std::endl;
    return 0;
}
