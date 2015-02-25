#include "stringKernel.h"

stringKernel::stringKernel(string ipath, double lambda) : vtKernel(ipath)
{
    _lambda = lambda;
}

double stringKernel::sentenceKernel(Graph* graph1, Graph* graph2)
{
    double sum = 0;
    for (unsigned int i=0; i<graph1->label_list.size(); i++){
        for (unsigned int j=0; j<graph2->label_list.size(); j++){
            sum += this->_lexicalKernel(graph1->label_list[i], graph2->label_list[j]);
        }
    }
    return sum;
}
