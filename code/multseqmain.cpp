#include <iostream>
#include "matrix.hpp"
#include "multseqmatrix.hpp"

int main(int argc, char const *argv[])
{
    int height = 5, width = 7;
    int mini = -height/2;
    matrix_t m1 = generate(height, width, mini);
    matrix_t m2 = generate(width, height, height*width);
    matrix_t mult = multiplySEQ(m1, m2);
    print_matrix(m1);
    std::cout << std::endl;
    print_matrix(m2);
    std::cout << std::endl;
    print_matrix(mult);
    return 0;
}
