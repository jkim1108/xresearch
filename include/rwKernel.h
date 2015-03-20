#ifndef RWKERNEL_H
#define RWKERNEL_H

#include "main.h"
#include "vtKernel.h"

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <Eigen/SparseCore>

using namespace std;
using namespace Eigen;

class rwKernel : public vtKernel
/*
    Random walk kernel
*/
{
    public:
        rwKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* graph1, const depTree* graph2);

    protected:
        void _makeProductAdjMatrix(SparseMatrix<double, RowMajor>& adjMatrix, const Graph* graph1, const Graph* graph2);
};

#endif // RWKERNEL_H
