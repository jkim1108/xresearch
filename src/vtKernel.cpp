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

double vtKernel::docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2)
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

double vtKernel::_deltaKernel(string& word1, string& word2)
/*
    Outputs the dirac delta kernel value between two words
*/
{
    return (word1 == word2);
}

double vtKernel::_lexicalKernel(string& word1, string& word2)
/*
    Laplacian kernel for the lexical similarity between two words
*/
{
    if (word1 == word2)
    {
        return 1.;
    }

    VectorXd emb1 = _embedding[word1];
    VectorXd emb2 = _embedding[word2];

    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        VectorXd diff = emb1 - emb2;
        return exp(-.1 * diff.norm());
    }
}

double vtKernel::_laplacianKernel(VectorXd emb1, VectorXd emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        VectorXd diff = emb1 - emb2;
        return exp(-.1 * diff.norm());
    }
}
;


