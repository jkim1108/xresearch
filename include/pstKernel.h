#ifndef PSTKERNEL_H
#define PSTKERNEL_H
#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

class pstKernel : public vtKernel
/*
    Subtree Kernel defined as the sum of products of word kernels
    rather than the sum of sums
*/
{
    public:
        pstKernel(string ipath, double lambda, int maxLength, bool useSent=false);
        double sentenceKernel(Graph* graph1, Graph* graph2);
        double sentenceKernel(depTree* dt1, depTree* dt2);

    protected:
        double C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, double pre=0, double multi=1);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l);
};

#endif // PSTKERNEL_H
