#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>
#include <type_traits>
#include <climits>
#include <cmath>

int main()
{
    Test test1(TESTtestSquaringX, testSquaringX, "testSquaringX(int x)");
    test1.runTest();
    return 0;
}

template <typename T, typename U>
struct Test
{
    const char *_testname;
    std::vector<std::tuple<T, U>> _cases;
    U (*_func)(T);

    Test(std::vector<std::tuple<T, U>> in, U (*f)(T), const char *testname)
        : _testname(testname), _cases(in), _func(f)
    {
        static_assert(std::is_same<U, decltype(_func(std::declval<T>()))>,
                      "Expected result type U must match test function's return type");
    }

    void runTest()
    {
        for (const std::tuple<T, U> &testcase : _cases)
        {
            T argsIn = std::get<0>(testcase);
            U expected = std::get<1>(testcase);
            try
            {
                U result = _func(argsIn);

                if (result == expected)
                {
                    std::cout << "TEST: " << _testname << " PASSED" << std::endl;
                }
                else
                {
                    std::cout << "TEST: " << _testname << " FAILED WITH INPUT: " << tostring(argsIn) << " and expected output: " << tostring(expected) << std::endl;
                }
            }
            catch (const std::runtime_error &error)
            {
                std::cerr << "Error: " << error.what() << " when invoking test: " << _testname << std::endl;
            }
        }
    }
};

// cases for testSquaringX(int x)
std::vector<std::tuple<int, int>> TESTtestSquaringX = {
    {2, 4},
    {46340, 2147395600},
    {46341, 0},
    {-46341, 0}};

int testSquaringX(int x)
{
    try
    {
        if (x > std::sqrt(INT_MAX))
        {
            throw std::runtime_error("THAT INT IS TOO BIG DUDE");
        }
        else if (x < -std::sqrt(INT_MAX))
        {
            throw std::runtime_error("THAT INT IS TOO SMALL DUDE");
        }
        int res = x * x;
        return res;
    }
    catch (const std::runtime_error &error)
    {
        std::cerr << "Runtime error occurred: " << error.what() << std::endl;
        return -1;
    }
}
