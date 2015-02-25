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
        int l =  min(graph1->label_list.size()-i, graph2->label_list.size()-j);
        return (_lambda * (1 - pow(_lambda, l)))/(1-_lambda) *
               this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]) +
               _lambda * C(graph1, graph2, i+1, j+1);
    }
};

double stKernel::sentenceKernel(depTree* dt1, depTree* dt2)
{
    double sum = 0;
    for (unsigned int i=0; i<dt1->node_list.size(); i++){
        for (unsigned int j=0; j<dt2->node_list.size(); j++){
            int L = min(dt1->node_list[i]->height, dt2->node_list[j]->height);
            for (int l=0; l<L; l++){
                sum += C(dt1, dt2, i, j, l);
            }
        }
    }
    return sum;
};

double stKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l)
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
        double sum = this->_lexicalKernel(dt1->node_list[i]->label, dt2->node_list[j]->label);
        for (auto child1:dt1->node_list[i]->children)
        {
            for (auto child2:dt2->node_list[j]->children)
            {
                sum += _lambda * C(dt1, dt2, child1, child2, l-1);
            }
        }
        return sum;
    }
}
