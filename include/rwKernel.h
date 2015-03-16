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
        double docKernel(Graph* graph1, Graph* graph2);

    protected:
        void _makeProductAdjMatrix(SparseMatrix<double, RowMajor>& adjMatrix, Graph* graph1, Graph* graph2);
};

#endif // RWKERNEL_H
