#include "strKernel.h"

strKernel::strKernel(string ipath, double lambda, int maxLength,
                    bool useSent, double sigma1, double sigma2) :
                    vtKernel(ipath, lambda, maxLength, useSent, sigma1, sigma2)
                    {}

double strKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (unsigned int i=0; i<graph1->labelList.size(); i++)
    {
        for (unsigned int j=0; j<graph2->labelList.size(); j++)
        {
            sum += this->_wordKernel(graph1->labelList[i], graph2->labelList[j]);
        }
    }
    return sum;
}
