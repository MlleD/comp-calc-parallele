#include "multseqmatrix.hpp"
#include "multompmatrix.hpp"
#include "multcilkmatrix.hpp"
#include "multtbbmatrix.hpp"
#include <chrono>
#include <iostream>
#include <functional>
#include <algorithm>
long long calculateRuntime(
    std::function<matrix_t(matrix_t, matrix_t)> function, 
    matrix_t m1, matrix_t m2
)
{
    std::chrono::steady_clock::duration start, end;
    long long startCount, endCount;
    matrix_t result;

    start = std::chrono::steady_clock::now().time_since_epoch();
    result = function(m1, m2);
    end = std::chrono::steady_clock::now().time_since_epoch();
    endCount = std::chrono::duration_cast<std::chrono::milliseconds>(end).count();
    startCount = std::chrono::duration_cast<std::chrono::milliseconds>(start).count();
    return (endCount - startCount);
}

void print_runtime(long long runtime)
{
    std::cout << runtime << " ms" << std::endl;
}

long long run(int height, int width, int mini, std::function<matrix_t(matrix_t, matrix_t)> function)
{
    matrix_t m1, m2;
    long long runtime;

    m1 = generate(height, width, mini);
    m2 = generate(width, height, height*width);
    runtime = calculateRuntime(function, m1, m2);
    print_runtime(runtime);
    return runtime;
}

std::pair<long long, long long> extrema(std::vector<long long> v)
{
    const auto minmax = std::minmax_element(v.begin(), v.end());
    int i_min = std::distance(v.begin(), minmax.first);
    int i_max = std::distance(v.begin(), minmax.second);
    std::pair<long long, long long> result = std::make_pair(v[i_min], v[i_max]);
    return result;
}

long long calc_mean(std::vector<long long> v)
{
    long long sum = 0;
    int nb = v.size();
    for (int i = 0; i < nb; i++)
    {
        sum += v[i]; 
    }
    return sum / nb;
}

int main(int argc, char const *argv[])
{
    int mini;
    std::vector<int> heights = {
        100, 250, 500, 750, 1000,
        100, 150, 200, 300, 450, 600, 900,
        100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
        1000, 2000, 3000, 4000, 5000, 6000, 7000
    };
    std::vector<int> widths = {
        100, 250, 500, 750, 1000,
        900, 600, 450, 300, 200, 150, 100,
        1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
        100, 100, 100, 100, 100, 100, 100
    };
    int size = heights.size();
    int nbiter = 10;
    int nbdata = 4 * size;

    std::vector<std::vector<long long>> alldata(nbdata, std::vector<long long>(nbiter));

    for (int numTest = 0; numTest < (4 * size - 3); numTest += 4)
    {
        std::cout << "Runtime per matrix size" << std::endl;

        for (int numIter = 0; numIter < nbiter; numIter++)
        {
            int i = numTest / 4;
            std::cout << "- Two matrices " << heights[i] << "x" << widths[i] << std::endl;
            mini = -heights[i] / 2;
            std::cout << "\tSequential: ";
            alldata[numTest][numIter] = run(heights[i], widths[i], mini, &multiplySEQ);
            std::cout << "\tOpen MP: ";
            alldata[numTest + 1][numIter] = run(heights[i], widths[i], mini, &multiplyOMP);
            std::cout << "\tCilk: ";
            alldata[numTest + 2][numIter] = run(heights[i], widths[i], mini, &multiplyCILK);
            std::cout << "\tTbb: ";
            alldata[numTest + 3][numIter] = run(heights[i], widths[i], mini, &multiplyTBB);
        }
    }

    int nbstats = 3;
    std::vector<std::vector<long long>> stats(nbdata, std::vector<long long>(nbstats));
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Compute some statistics" << std::endl;
    std::cout << "Modes: 0 = Sequential, 1 = OpenMP, 2 = Cilk, 3 = TBB" << std::endl;
    for (int i = 0; i < nbdata; i++)
    {
        std::cout << "Test #" << (i/4) << "in mode " << (i % 4) << " : " << std::endl;
        std::pair<long long, long long> extrem = extrema(alldata[i]);
        std::cout << "\tMinimum ";
        print_runtime(extrem.first);
        stats[i][0] = extrem.first;
        std::cout << "\tMaximum ";
        print_runtime(extrem.second);
        stats[i][1] = extrem.second;
        long long m = calc_mean(alldata[i]);
        std::cout << "\tMean (floor rounding) ";
        print_runtime(m);
        stats[i][2] = m;
    }

    std::cout << "-----------------------------" << std::endl;
    std::cout << "Print statistics in CSV format" << std::endl;
    std::cout << "Minimum,Maximum,Mean" << std::endl;

    for (std::vector<long long> stat_row: stats)
    {
        int limit = nbstats - 1;
        for (int i = 0; i < limit; i++)
        {
            std::cout << stat_row[i] << ",";
        }
        std::cout << stat_row[limit] << std::endl;
    }

    return 0;
}
