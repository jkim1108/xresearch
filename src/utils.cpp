#include "main.h"
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


