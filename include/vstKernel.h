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
        double C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        double C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre);
        double _distortion;

};

#endif // VSTKERNEL_H
