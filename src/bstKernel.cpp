#include "bstKernel.h"

bstKernel::bstKernel(string ipath, double lambda, int maxLength, bool useSent) : vtKernel(ipath, lambda, maxLength, useSent){}

std::ostream& operator<< (std::ostream& stream, const bstKernel& bk)
{
  return stream << "bstKernel_" << bk._lambda;
}

double bstKernel::sentenceKernel(Graph* graph1, Graph* graph2)
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

double bstKernel::C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre)
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
        newPre.value = pre.value + _laplacianKernel(newPre.baryCentre1, newPre.baryCentre2, 10.) * pow(_lambda, pre.length);
        newPre.length = pre.length + 1;
        return C(graph1, graph2, i+1, j+1, l-1, newPre);
    }
}

double bstKernel::sentenceKernel(depTree* dt1, depTree* dt2)
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
};

double bstKernel::C(depTree* dt1, depTree* dt2, int i, int j, int l, preComputed& pre)
{
    if ((l==0) or (dt1->nodeList[i]->height==0) or (dt2->nodeList[j]->height==0))
    {
        auto baryCentre1 = _updateBaryCentre(pre.baryCentre1, pre.length, _embedding[dt1->nodeList[i]->label]);
        auto baryCentre2 = _updateBaryCentre(pre.baryCentre2, pre.length, _embedding[dt2->nodeList[j]->label]);
        return _laplacianKernel(baryCentre1, baryCentre2, 10.) * pow(_lambda, pre.length);
    }

    else
    {
        preComputed newPre;
        newPre.baryCentre1 = _updateBaryCentre(pre.baryCentre1, pre.length, _embedding[dt1->nodeList[i]->label]);
        newPre.baryCentre2 = _updateBaryCentre(pre.baryCentre2, pre.length, _embedding[dt2->nodeList[j]->label]);
        double sum = _laplacianKernel(newPre.baryCentre1, newPre.baryCentre2, 10.) * pow(_lambda, pre.length);
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
