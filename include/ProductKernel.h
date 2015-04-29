#ifndef ProductKernel_H
#define ProductKernel_H
#include "main.h"
#include "Kernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

class ProductKernel : public Kernel
/*
    Subtree Kernel defined as the sum of products of word kernels
    rather than the sum of sums
*/
{
    public:
        ProductKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* dt1, const depTree* dt2);

    protected:
        double C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, double pre=0, double multi=1);
        double C(const depTree* dt1, const depTree* dt2, int i, int j, int l);
};

#endif // ProductKernel_H
