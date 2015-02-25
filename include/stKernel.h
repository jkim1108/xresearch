#ifndef STKERNEL_H
#define STKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

class stKernel : public vtKernel
/*
    Subtree Kernel
*/
{
    public:
        stKernel(string ipath, double lambda);
        double sentenceKernel(Graph* graph1, Graph* graph2);
        double sentenceKernel(depTree* dt1, depTree* dt2);

    protected:
        double C(Graph* graph1, Graph* graph2, int i, int j);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l);
        double _lambda;
};

#endif // STKERNEL_H
