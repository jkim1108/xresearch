#ifndef VSTKERNEL_H
#define VSTKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <bstKernel.h>


class vstKernel : public bstKernel
{
    public:
        vstKernel(Options opt);
    protected:
        double C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l, preComputed& pre);

};

#endif // VSTKERNEL_H
