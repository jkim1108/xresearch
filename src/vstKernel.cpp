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
        newPre.baryCentre1 = _updateBaryCentre(pre.baryCentre1, pre.length, _embedding[graph1->labelList[i]]);
        newPre.baryCentre2 = _updateBaryCentre(pre.baryCentre2, pre.length, _embedding[graph2->labelList[j]]);
        newPre.value = pre.value;
        newPre.value += _wordKernel(newPre.baryCentre1, newPre.baryCentre2) * pow(_lambda, pre.length);
        if (pre.length > 0)
        {
            newPre.value +=  _wordKernel(pre.baryCentre1, newPre.baryCentre2) * pow(_lambda, pre.length) * _distortion;
            newPre.value +=  _wordKernel(pre.baryCentre2, newPre.baryCentre1) * pow(_lambda, pre.length) * _distortion;
        }
        newPre.length = pre.length + 1;
        return C(graph1, graph2, i+1, j+1, l-1, newPre);
    }
}

double vstKernel::C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre)
{
    if ((l==0) or (dt1->nodeList[i]->height==0) or (dt2->nodeList[j]->height==0))
    {
        auto baryCentre1 = _updateBaryCentre(pre.baryCentre1, pre.length, _embedding[dt1->nodeList[i]->label]);
        auto baryCentre2 = _updateBaryCentre(pre.baryCentre2, pre.length, _embedding[dt2->nodeList[j]->label]);
        return _wordKernel(baryCentre1, baryCentre2) * pow(_lambda, pre.length);
    }

    else
    {
        preComputed newPre;
        newPre.baryCentre1 = _updateBaryCentre(pre.baryCentre1, pre.length, _embedding[dt1->nodeList[i]->label]);
        newPre.baryCentre2 = _updateBaryCentre(pre.baryCentre2, pre.length, _embedding[dt2->nodeList[j]->label]);
        double sum = _wordKernel(newPre.baryCentre1, newPre.baryCentre2) * pow(_lambda, pre.length);
        if (pre.length)
        {
            newPre.value +=  _wordKernel(pre.baryCentre1, newPre.baryCentre2) * pow(_lambda, pre.length);
            newPre.value +=  _wordKernel(pre.baryCentre2, newPre.baryCentre1) * pow(_lambda, pre.length);
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
