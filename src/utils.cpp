#include "main.h"
#include <iostream>
#include <cmath>
#include <cassert>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <thread>

using namespace Eigen;
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

double diffusionKernel(SparseMatrix<float>& adj_matrix, int n)
/*
    Outputs the diffusion kernel values (sum of all the elements in the exponential
    of adjacency matrix) computed up to n-th term
*/
{
    double lambda = 1.;
    int i = 1;
    SparseMatrix <float, RowMajor> acc_matrix(adj_matrix);

    double sum = lambda * acc_matrix.row(0).sum();
    //sum = 0.;
    while(i++<n)
    {
        //cout << sum << endl;
        acc_matrix = acc_matrix * adj_matrix;
        sum += acc_matrix.row(0).sum() / factorial(i); //* pow(lambda, i);
    }
    //cout << sum << endl;
    //cout << endl;
    return sum;
}

