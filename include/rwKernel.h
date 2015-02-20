#ifndef RWKERNEL_H
#define RWKERNEL_H

#include "main.h"
#include "vtKernel.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace Eigen;
using namespace std;

class rwKernel : public vtKernel
{
    public:
        rwKernel(string ipath);
        double sentenceKernel(Graph * graph1, Graph * graph2);

    protected:

        inline double _wordKernel(string & word1, string & word2);
        inline double _lexicalKernel(string & word1, string & word2);
        inline double _sentimentKernel(string & word1, string & word2);
        inline double _deltaKernel(string & word1, string & word2);
        void _makeProductAdjMatrix(SparseMatrix <float> * adj_matrix, Graph* graph1, Graph* graph2);

        VectorXd _sent_vector;

};

#endif // RWKERNEL_H
