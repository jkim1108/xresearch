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
            int L = min(graph1->label_list.size() - i, graph2->label_list.size() - j) - 1;
            sum += C(graph1, graph2, i, j, L);
        }
    }
    return sum;
};

double pstKernel::C(Graph* graph1, Graph* graph2, int i, int j, int l, double pre)
{
    if (l == 0)
    {
        return this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) * (1 + _lambda * pre);
    }
    else
    {
        pre = this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) * (1 + _lambda * pre);
        return C(graph1, graph2, i+1, j+1, l-1, pre);
    }
};

double pstKernel::sentenceKernel(depTree* dt1, depTree* dt2)
{
    double sum = 0;
    for (unsigned int i=0; i<dt1->node_list.size(); i++){
        for (unsigned int j=0; j<dt2->node_list.size(); j++){
            int L = min(dt1->node_list[i]->height, dt2->node_list[j]->height) + 1;
            for (int l=0; l<L; l++){
                sum += C(dt1, dt2, i, j, l);
            }
        }
    }
    return sum;
};

double pstKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l)
{
    if ((l > dt1->node_list[i]->height) || (l > dt2->node_list[j]->height))
    {
        return 0.;
    }

    else if (l == 0)
    {
        return this->_lexicalKernel(dt1->node_list[i]->label, dt2->node_list[j]->label);
    }

    else
    {
        double sum = 0.;
        double cur = this->_lexicalKernel(dt1->node_list[i]->label, dt2->node_list[j]->label);
        for (auto child1:dt1->node_list[i]->children)
        {
            for (auto child2:dt2->node_list[j]->children)
            {
                sum += _lambda * cur * C(dt1, dt2, child1, child2, l-1);
            }
        }
        return sum;
    }
}
