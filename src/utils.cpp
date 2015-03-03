#include "main.h"
#include "vtKernel.h"
#include "rwKernel.h"
#include "stringKernel.h"
#include "pstKernel.h"
#include "bstKernel.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;
using namespace boost::numeric;

pair<int, int> vectorToPair(std::vector<int> input)
/*
    Convert two dimensional vectors to std::pair
*/
{
    assert(input.size()==2);
    pair<int, int> res;
    res.first = input[0];
    res.second = input[1];
    return res;
};

double factorial(int n)
/*
    Factorial function
*/
{
    assert(n>=0);
    if (n==0) return 1.;
    else return double(n) * factorial(n-1);
};

/*
vtKernel* kernelChooser(char kernelName, string ipath, double lambda, int maxLength, bool useSent)
{
    switch(kernelName)
    {
        case 'b':
            auto kernel = new bstKernel(ipath, lambda, maxLength, useSent);
            return kernel;
        case 's':
            auto kernel = new stringKernel(ipath, lambda, maxLength, useSent);
            return kernel;
        case 'p':
            auto kernel = new pstKernel(ipath, lambda, maxLength, useSent);
            return kernel;
        case 'r':
            auto kernel = new rwKernel(ipath, lambda, maxLength, useSent);
            return kernel;
    }
}

*/
