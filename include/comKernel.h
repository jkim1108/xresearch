#ifndef COMKERNEL_H
#define COMKERNEL_H

#include "main.h"
#include "vtKernel.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace std;
using namespace Eigen;

class comKernel : public vtKernel
{
    public:
        comKernel(string ipath);
        double sentenceKernel(Graph * graph1, Graph * graph2);

    protected:
        VectorXd _centre_of_mass(Graph * graph);

};

#endif // COMKERNEL_H
