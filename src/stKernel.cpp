#include "stKernel.h"

stKernel::stKernel(string ipath, double lambda) : vtKernel(ipath)
/*
    Set the decaying factor
*/
{
    _lambda = lambda;
}

double stKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (unsigned int i=0; i<graph1->label_list.size(); i++){
        for (unsigned int j=0; j<graph2->label_list.size(); j++){
            sum += C(graph1, graph2, i, j);
        }
    }
    return sum;
};

double stKernel::C(Graph* graph1, Graph* graph2, int i, int j)
{
    if ((i >= graph1->label_list.size()) || (j >= graph2->label_list.size()))
    {
        return 0.;
    }

    else
    {
        int l = L(graph1, graph2, i, j);
        return (_lambda * (1 - pow(_lambda, l)))/(1-_lambda) *
               this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) +
               _lambda * C(graph1, graph2, i+1, j+1);
    }
};

int stKernel::L(Graph* graph1, Graph* graph2, int i, int j)
{
    return min(graph1->label_list.size()-i, graph2->label_list.size()-j);
};
