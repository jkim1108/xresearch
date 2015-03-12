#ifndef STRKERNEL_H
#define STRKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>
#include <unordered_map>

class strKernel : public vtKernel
{
    public:
        strKernel(Options opt);
        double docKernel(Graph* graph1, Graph* graph2);
    protected:
};

#endif // STRKERNEL_H
