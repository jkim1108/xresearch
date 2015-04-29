#ifndef VectorTreeKernel_H
#define VectorTreeKernel_H

#include "main.h"
#include "Kernel.h"

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <Eigen/SparseCore>

using namespace std;
using namespace Eigen;

class VectorTreeKernel : public Kernel
/*
    Random walk kernel
*/
{
    public:
        VectorTreeKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* graph1, const depTree* graph2);

    protected:
        void _makeProductAdjMatrix(SparseMatrix<double, RowMajor>& adjMatrix, const Graph* graph1, const Graph* graph2);
};

#endif // VectorTreeKernel_H
