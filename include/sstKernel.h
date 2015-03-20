#ifndef SSTKERNEL_H
#define SSTKERNEL_H

#include <main.h>
#include <vtKernel.h>

class sstKernel : public vtKernel
/*
    Sparse Subtree Kernel
*/
{
    public:
        sstKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);

    protected:
        double K(const Graph* graph1, const Graph* graph2, int q, int i, int j);
        double C(const Graph* graph1, const Graph* graph2, int q, int i, int j, double a);
        double C(const Graph* graph1, const Graph* graph2, int q, int i, int j);
        double C(const Graph* graph1, const Graph* graph2, int q, int r, int i, int j);
        double Cp(const Graph* graph1, const Graph* graph2, int q, int i, int j);
        double Cp(const Graph* graph1, const Graph* graph2, int q, int r, int i, int j);
};

#endif // SSTKERNEL_H
