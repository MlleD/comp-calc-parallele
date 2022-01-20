#include "matrix.hpp"
#include <iostream>
#include <algorithm>
matrix_t generate(int height, int width, int min)
{
    matrix_t result(height, std::vector<int>(width));
    int current_min = min;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            result[i][j] = current_min + j;
        }
        current_min += width;
        std::random_shuffle(result[i].begin(), result[i].end());
    }
    std::random_shuffle(result.begin(), result.end());
    return result;
}

void print_matrix(matrix_t matrix)
{
    std::for_each(matrix.begin(), matrix.end(), [](std::vector<int> v) {
        for (int i: v)
            std::cout << i << " ";
        std::cout<< std::endl;
    });
}
