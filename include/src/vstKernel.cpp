#include "vstKernel.h"

vstKernel::vstKernel(Options opt) : bstKernel(opt), _distortion(opt.distortion) {}

double vstKernel::C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre)
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
        newPre.value = pre.value;
        newPre.value += _wordKernel(newPre.compVector1, newPre.compVector2) * pow(_lambda, pre.length);
        if (pre.length > 0)
        {
            newPre.value +=  _wordKernel(pre.compVector1, newPre.compVector2) * pow(_lambda, pre.length) * _distortion;
            newPre.value +=  _wordKernel(pre.compVector2, newPre.compVector1) * pow(_lambda, pre.length) * _distortion;
        }
        newPre.length = pre.length + 1;
        return C(graph1, graph2, i+1, j+1, l-1, newPre);
    }
}

double vstKernel::C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre)
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
        if (pre.length)
        {
            newPre.value +=  _wordKernel(pre.compVector1, newPre.compVector2) * pow(_lambda, pre.length);
            newPre.value +=  _wordKernel(pre.compVector2, newPre.compVector1) * pow(_lambda, pre.length);
        }
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
