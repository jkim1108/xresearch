#ifndef STRINGKERNEL_H
#define STRINGKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>


class stringKernel : public vtKernel
{
    public:
        stringKernel(string ipath);
        double sentenceKernel(Graph* graph1, Graph* graph2);
    protected:
};

#endif // STRINGKERNEL_H
