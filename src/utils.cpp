#include "main.h"
#include "vtKernel.h"
#include "rwKernel.h"
#include "strKernel.h"
#include "pstKernel.h"
#include "bstKernel.h"

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

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
}

double factorial(int n)
/*
    Factorial function
*/
{
    assert(n>=0);
    if (n==0) return 1.;
    else return double(n) * factorial(n-1);
}

