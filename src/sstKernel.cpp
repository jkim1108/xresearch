#include "sstKernel.h"

sstKernel::sstKernel(string ipath, double lambda) : vtKernel(ipath)
/*
    Set the decaying factor
*/
{
    _lambda = lambda;
}

double sstKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    int n = graph1->label_list.size();
    int m = graph2->label_list.size();
    for (int q=0; q<min(m, n); q++)
    {
        sum += K(graph1, graph2, q, m, n);
    }
    return sum;
};


double sstKernel::K(Graph* graph1, Graph* graph2, int q, int i, int j)
{
    double sum = _lambda * this->K(graph1, graph2, q, i, j-1);
    for (int s=0; s<i; s++)
    {
        sum += _lambda * _lambda * C(graph1, graph2, q-1, s-1, j-1,
                this->_lexicalKernel(graph1->label_list[s], graph2->label_list[j]));
    }
    return sum;
};

double sstKernel::C(Graph* graph1, Graph* graph2, int q, int i, int j, double a)
{
    double sum = a * C(graph1, graph2, q, i, j);
    for (int r=0; r<q; r++)
    {
        sum += C(graph1, graph2, q, r, i, j);
    }
}

double sstKernel::C(Graph* graph1, Graph* graph2, int q, int i, int j)
{
    return _lambda * C(graph1, graph2, q, i, j-1) + Cp(graph1, graph2, q, i, j);
}

double sstKernel::Cp(Graph* graph1, Graph* graph2, int q, int i, int j)
{
    return _lambda * _lambda * C(graph1, graph2, q-1, i-1, j-1) + _lambda * Cp(graph1, graph2, q, i, j-1);
}

double sstKernel::C(Graph* graph1, Graph* graph2, int q, int r, int i, int j)
{
    return _lambda * C(graph1, graph2, q, r, i, j-1) + Cp(graph1, graph2, q, r, i, j);
}

double sstKernel::Cp(Graph* graph1, Graph* graph2, int q, int r, int i, int j)
{
	if (q != r)
    {
        return _lambda * _lambda * C(graph1, graph2, q-1, r, i-1, j-1) + _lambda * Cp(graph1, graph2, q, r, i, j-1);
    }

    else
    {
        return _lambda * _lambda * this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) *
                C(graph1, graph2, q-1, i-1, j-1) + _lambda * Cp(graph1, graph2, q, r, i, j-1);
    }
}
