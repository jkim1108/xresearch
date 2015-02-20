#include "vtKernel.h"
#include <iostream>
#include <algorithm>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace Eigen;
using namespace boost::numeric::ublas;
using namespace std;

vtKernel::vtKernel(string ipath)
/*
    Assign the embedding dictionary and sentiment vector which shall be used for
    the computation of the kernel
*/
{
    _embedding = loadEmbedding(ipath);
};

/*
vtKernel::~vtKernel()
//Destructor freeing memory used by embedding and sent vector
{
    delete &_sent_vector;
    _embedding.clear();
    delete &_embedding;
};
*/

double vtKernel::doc_kernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2)
/*
    Document kernel computed as the sum of random walk kernel values between all
    pairs of sentences in doc1 and doc2
*/
{
    double res(0);
    for (auto graph1 : doc1)
    {
        for (auto graph2 : doc2)
        {
            res += this->sentenceKernel(graph1, graph2);
        }
    }
    return res;
}

