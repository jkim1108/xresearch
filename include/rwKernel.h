#ifndef RWKERNEL_H
#define RWKERNEL_H

#include "main.h"
#include "vtKernel.h"

#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;
using namespace boost::numeric;

class rwKernel : public vtKernel
/*
    Random walk kernel
*/
{
    public:
        rwKernel(string ipath, double lambda, int maxLength);
        double sentenceKernel(Graph* graph1, Graph* graph2);

    protected:
        double _wordKernel(string& word1, string& word2);
        double _sentimentKernel(string& word1, string& word2);
        void _makeProductAdjMatrix(ublas::compressed_matrix<double>& adjMatrix, Graph* graph1, Graph* graph2);
        ublas::vector<double> _sent_vector;
        double _lambda;
        int _maxLength;
};

#endif // RWKERNEL_H
