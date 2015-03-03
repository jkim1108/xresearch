#include "stringKernel.h"

stringKernel::stringKernel(string ipath, double lambda, int maxLength, bool useSent) : vtKernel(ipath, lambda, maxLength, useSent){}

double stringKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (unsigned int i=0; i<graph1->labelList.size(); i++)
    {
        for (unsigned int j=0; j<graph2->labelList.size(); j++)
        {
            sum += this->_lexicalKernel(graph1->labelList[i], graph2->labelList[j]);
        }
    }
    return sum;
}
