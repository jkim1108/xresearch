#ifndef BKERNEL_H
#define BKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

class bKernel: public vtKernel
/*
    Subtree Kernel defined as the sum of products of word kernels
    rather than the sum of sums
*/
{
    public:
        bKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* dt1, const depTree* dt2);

    protected:
        double C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, double pre=0, double multi=1);
        double C(const depTree* dt1, const depTree* dt2, int i, int j, int l);
};

#endif // PSTKERNEL_H
