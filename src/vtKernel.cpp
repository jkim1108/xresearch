#include "vtKernel.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace boost::numeric;
using namespace std;

vtKernel::vtKernel(string ipath, double lambda, int maxLength, bool useSent)
/*
    Assign the embedding dictionary and sentiment vector which shall be used for
    the computation of the kernel
*/
{
    _embedding = loadEmbedding(ipath);
    _lambda = lambda;
    _maxLength = maxLength;
    _useSent = useSent;
    _sent_vector = _embedding["good"] - _embedding["bad"];
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

    ublas::vector<double> emb1 = _embedding[word1];
    ublas::vector<double> emb2 = _embedding[word2];

    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        ublas::vector<double> diff = emb1 - emb2;
        return exp(-.1 * norm_1(diff));
    }
}

double vtKernel::_laplacianKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        ublas::vector<double> diff = emb1 - emb2;
        return exp(-.1 * norm_1(diff));
    }
}
;


