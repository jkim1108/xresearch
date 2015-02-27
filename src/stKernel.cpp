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
    for (unsigned int i=0; i<graph1->labelList.size(); i++){
        for (unsigned int j=0; j<graph2->labelList.size(); j++){
            sum += C(graph1, graph2, i, j);
        }
    }
    return sum;
};

double stKernel::C(Graph* graph1, Graph* graph2, int i, int j)
{
    if ((i >= graph1->labelList.size()) || (j >= graph2->labelList.size()))
    {
        return 0.;
    }

    else
    {
        int l =  min(graph1->labelList.size()-i, graph2->labelList.size()-j);
        return (_lambda * (1 - pow(_lambda, l)))/(1-_lambda) *
               this->_lexicalKernel(graph1->labelList[i], graph2->labelList[j]) +
               _lambda * C(graph1, graph2, i+1, j+1);
    }
};

double stKernel::sentenceKernel(depTree* dt1, depTree* dt2)
{
    double sum = 0;
    for (unsigned int i=0; i<dt1->nodeList.size(); i++){
        for (unsigned int j=0; j<dt2->nodeList.size(); j++){
            int L = min(dt1->nodeList[i]->height, dt2->nodeList[j]->height);
            for (int l=0; l<L; l++){
                sum += C(dt1, dt2, i, j, l);
            }
        }
    }
    return sum;
};

double stKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l)
{
    if ((l > dt1->nodeList[i]->height) || (l > dt2->nodeList[j]->height))
    {
        return 0.;
    }

    else if (l == 0)
    {
        return this->_lexicalKernel(dt1->nodeList[i]->label, dt2->nodeList[j]->label);
    }

    else
    {
        double sum = this->_lexicalKernel(dt1->nodeList[i]->label, dt2->nodeList[j]->label);
        for (auto child1:dt1->nodeList[i]->children)
        {
            for (auto child2:dt2->nodeList[j]->children)
            {
                sum += _lambda * C(dt1, dt2, child1, child2, l-1);
            }
        }
        return sum;
    }
}
