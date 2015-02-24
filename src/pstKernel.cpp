#include "pstKernel.h"

pstKernel::pstKernel(string ipath, double lambda) : vtKernel(ipath)
{
    _lambda = lambda;
}

double pstKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (int i=0; i<graph1->label_list.size(); i++)
    {
        for (int j=0; j<graph2->label_list.size(); j++)
        {
            int L = min(graph1->label_list.size() - i, graph2->label_list.size() - j);
            for (int l=0; l<L; l++)
            {
                sum += C(graph1, graph2, i, j, l);
            }
        }
    }
    return sum;
};

double pstKernel::C(Graph* graph1, Graph* graph2, int i, int j, int l)
{

    if ((i >= graph1->label_list.size()) || (j >= graph2->label_list.size()))
    {
        return 0.;
    }

    else if (l == 0)
    {
        return this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]);
    }

    else
    {
        return _lambda * this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) * C(graph1, graph2, i+1, j+1, l-1);
    }
};

