#ifndef PSTKERNEL_H
#define PSTKERNEL_H
#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>

class pstKernel : public vtKernel
/*
    Subtree Kernel defined as the sum of products of word kernels
    rather than the sum of sums
*/
{
    public:
        pstKernel(string ipath, double lambda, int maxLength);
        double sentenceKernel(Graph* graph1, Graph* graph2);
        double sentenceKernel(depTree* dt1, depTree* dt2);

    protected:
        double C(Graph* graph1, Graph* graph2, int i, int j, int l, double pre=0, double multi=1);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l);
        double _lambda;
        int _maxLength;

};

#endif // PSTKERNEL_H
