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
        sstKernel(string ipath, double lambda);
        double sentenceKernel(Graph* graph1, Graph* graph2);

    protected:
        double K(Graph* graph1, Graph* graph2, int q, int i, int j);
        double C(Graph* graph1, Graph* graph2, int q, int i, int j, double a);
        double C(Graph* graph1, Graph* graph2, int q, int i, int j);
        double C(Graph* graph1, Graph* graph2, int q, int r, int i, int j);
        double Cp(Graph* graph1, Graph* graph2, int q, int i, int j);
        double Cp(Graph* graph1, Graph* graph2, int q, int r, int i, int j);
        double _lambda;
};

#endif // SSTKERNEL_H
