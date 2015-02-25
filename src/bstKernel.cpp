#include "bstKernel.h"

bstKernel::bstKernel(string ipath, double lambda) : vtKernel(ipath)
{
    _lambda = lambda;
}

double bstKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (int i=0; i<graph1->label_list.size(); i++)
    {
        for (int j=0; j<graph2->label_list.size(); j++)
        {
            int L = min(graph1->label_list.size() - i, graph2->label_list.size() - j) ;
            preComputed pre;
            sum += C(graph1, graph2, i, j, L, pre);
        }
    }
    return sum;
}

double bstKernel::C(Graph* graph1, Graph* graph2, int i, int j, int l, preComputed& pre)
{
    if (l == 0)
    {
        return pre.value;
    }

    else
    {
        preComputed newPre;
        VectorXd newVector1 = _embedding[graph1->label_list[i]];
        VectorXd newVector2 = _embedding[graph2->label_list[j]];
        newPre.bariCentre1 = _updateBariCentre(pre.bariCentre1, pre.length, newVector1);
        newPre.bariCentre2 = _updateBariCentre(pre.bariCentre2, pre.length, newVector2);
        newPre.value = pre.value + _laplacianKernel(newPre.bariCentre1, newPre.bariCentre2) * pow(_lambda, pre.length);
        newPre.length = pre.length + 1;
        return C(graph1, graph2, i+1, j+1, l-1, newPre);
    }

}


double bstKernel::sentenceKernel(depTree* dt1, depTree* dt2)
{

}

double bstKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l)
{

}
