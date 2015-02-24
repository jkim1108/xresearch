#ifndef PSTKERNEL_H
#define PSTKERNEL_H
#include "main.h"
#include "vtKernel.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>

class pstKernel : public vtKernel
{
    public:
        pstKernel(string ipath, double lambda);
        double sentenceKernel(Graph* graph1, Graph* graph2);
    protected:
        double C(Graph* graph1, Graph* graph2, int i, int j, int l);
        double _lambda;
};

#endif // PSTKERNEL_H
