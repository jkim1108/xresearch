#include "sstKernel.h"

sstKernel::sstKernel(string ipath, double lambda, int maxLength, bool useSent) : vtKernel(ipath, lambda, maxLength, useSent){}

double sstKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    int n = graph1->labelList.size();
    int m = graph2->labelList.size();
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
                this->_wordKernel(graph1->labelList[s], graph2->labelList[j]));
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
    return sum;
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
        return _lambda * _lambda * this->_wordKernel(graph1->labelList[i], graph2->labelList[j]) *
                C(graph1, graph2, q-1, i-1, j-1) + _lambda * Cp(graph1, graph2, q, r, i, j-1);
    }
}
