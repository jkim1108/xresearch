#include "bstKernel.h"

bstKernel::bstKernel(Options opt) :
                    vtKernel(opt)
                    {
                    }

double bstKernel::docKernel(const Graph* graph1, const Graph* graph2)
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
            preComputed pre;
            sum += C(graph1, graph2, i, j, L, pre);
        }
    }
    return sum;
}

double bstKernel::C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre)
{
    if ((l == 0) or (i>=graph1->labelList.size()) or (j>=graph2->labelList.size()))
    {
        return pre.value;
    }

    else
    {
        preComputed newPre;
        newPre.compVector1 = _updateComposition(pre.compVector1, _embedding[graph1->labelList[i]], pre.length);
        newPre.compVector2 = _updateComposition(pre.compVector2, _embedding[graph2->labelList[j]], pre.length);
        newPre.value = pre.value + _wordKernel(newPre.compVector1, newPre.compVector2) * pow(_lambda, pre.length);
        newPre.length = pre.length + 1;
        return C(graph1, graph2, i+1, j+1, l-1, newPre);
    }
}

double bstKernel::docKernel(const depTree* dt1, const depTree* dt2)
{
    double sum = 0;
    for (unsigned int i=0; i<dt1->nodeList.size(); i++)
    {
        for (unsigned int j=0; j<dt2->nodeList.size(); j++)
        {
            int L;
            if (_maxLength==0)
            {
                L = min(dt1->nodeList[i]->height, dt2->nodeList[j]->height);
            }
            else
            {
                L = _maxLength;
            }

            preComputed pre;
            sum += C(dt1, dt2, i, j, L, pre);
        }
    }
    return sum;
}

double bstKernel::C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre)
{
    if ((l==0) or (dt1->nodeList[i]->height==0) or (dt2->nodeList[j]->height==0))
    {
        auto compVector1 = _updateComposition(pre.compVector1, _embedding[dt1->nodeList[i]->label], pre.length);
        auto compVector2 = _updateComposition(pre.compVector2, _embedding[dt2->nodeList[j]->label], pre.length);
        return _wordKernel(compVector1, compVector2) * pow(_lambda, pre.length);
    }

    else
    {
        preComputed newPre;
        newPre.compVector1 = _updateComposition(pre.compVector1, _embedding[dt1->nodeList[i]->label], pre.length);
        newPre.compVector2 = _updateComposition(pre.compVector2, _embedding[dt2->nodeList[j]->label], pre.length);
        double sum = _wordKernel(newPre.compVector1, newPre.compVector2) * pow(_lambda, pre.length);
        newPre.length = pre.length + 1;

        for (auto child1:dt1->nodeList[i]->children)
        {
            for (auto child2:dt2->nodeList[j]->children)
            {
                sum += C(dt1, dt2, child1, child2, l-1, newPre);
            }
        }

        return sum;
    }
}
