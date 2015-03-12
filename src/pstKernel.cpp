#include "pstKernel.h"

pstKernel::pstKernel(Options opt) :
                    vtKernel(opt)
                    {}

double pstKernel::docKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (unsigned int i=0; i<graph1->labelList.size(); i++)
    {
        for (unsigned int j=0; j<graph2->labelList.size(); j++)
        {
            int L;
            if (_maxLength==0)
            {
                L = min(graph1->labelList.size() - i, graph2->labelList.size() - j) ;
            }
            else
            {
                L = _maxLength;
            }
            sum += C(graph1, graph2, i, j, L);
        }
    }
    return sum;
};

double pstKernel::C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, double pre, double multi)
{
    if ((l == 0) or (i>=graph1->labelList.size()) or (j>=graph2->labelList.size()))
    {
        return pre;
    }
    else
    {
        multi *= _lambda * _wordKernel(graph1->labelList[i], graph2->labelList[j]);
        pre += multi;
        return C(graph1, graph2, i+1, j+1, l-1, pre);
    }
};

double pstKernel::docKernel(depTree* dt1, depTree* dt2)
{
    double sum = 0;
    for (unsigned int i=0; i<dt1->nodeList.size(); i++)
    {
        for (unsigned int j=0; j<dt2->nodeList.size(); j++)
        {
            int L;
            if (_maxLength==0)
            {
                L = min(dt1->nodeList[i]->height, dt2->nodeList[j]->height) + 1;
            }
            else
            {
                L = _maxLength;
            }
            for (int l=0; l<L; l++)
            {
                sum += C(dt1, dt2, i, j, l);
            }
        }
    }
    return sum;
};

double pstKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l)
{
    if ((l > dt1->nodeList[i]->height) || (l > dt2->nodeList[j]->height))
    {
        return 0.;
    }

    else if (l == 0)
    {
        return this->_wordKernel(dt1->nodeList[i]->label, dt2->nodeList[j]->label);
    }

    else
    {
        double sum = 0.;
        double cur = this->_wordKernel(dt1->nodeList[i]->label, dt2->nodeList[j]->label);
        for (auto child1:dt1->nodeList[i]->children)
        {
            for (auto child2:dt2->nodeList[j]->children)
            {
                sum += _lambda * cur * C(dt1, dt2, child1, child2, l-1);
            }
        }
        return sum;
    }
}
