#include "main.h"
#include "vtKernel.h"
#include "parser.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace boost::numeric;
using namespace std;

vtKernel::vtKernel(Options opt)
/*
    Assign the embedding dictionary and sentiment vector which shall be used for
    the computation of the kernel
*/
{
    _embedding = loadEmbedding(getInputPath(opt.dataset));
    _lambda = opt.lambda;
    _maxLength = opt.maxLength;
    _useSent = opt.useSent;
    _useSWN = opt.useSWN;
    string PATH = "/home/kim/xresearch/";

    if (_useSWN)
    {
        _sent_vector = loadSentVec(PATH);
    }
    else
    {
        _sent_vector = _embedding["good"] - _embedding["bad"];
    }
    _sigma1 = opt.sigma1;
    _sigma2 = opt.sigma2;
}

/*
vtKernel::~vtKernel()
//Destructor freeing memory used by embedding and sent vector
{
    delete &_sent_vector;
    _embedding.clear();
    delete &_embedding;
};
*/
double vtKernel::sentenceKernel(depTree* graph1, depTree* graph2)
{
    return 0;
}

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

double vtKernel::docKernel(std::vector<depTree*> doc1, std::vector<depTree*> doc2)
{
    double res(0);
    for (auto dt1 : doc1)
    {
        for (auto dt2 : doc2)
        {
            res += this->sentenceKernel(dt1, dt2);
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
    auto emb1 = _embedding[word1];
    auto emb2 = _embedding[word2];
    return _lexicalKernel(emb1, emb2);
}

double vtKernel::_lexicalKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        /*
        auto diff = emb1 - emb2;
        return exp(-norm_2(diff)/_sigma1);
        */
        double sim = ublas::inner_prod(emb1, emb2);
        return (sim>0.4);
    }
}

double vtKernel::_sentimentKernel(string& word1, string& word2)
{
    if (word1 == word2)
    {
        return 1.;
    }
    auto emb1 = _embedding[word1];
    auto emb2 = _embedding[word2];
    return _sentimentKernel(emb1, emb2);
}

double vtKernel::_sentimentKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 1.;
    }
    else
    {
        ublas::vector<double> diff = emb1 - emb2;
        return exp(-abs(ublas::inner_prod(diff, _sent_vector))/_sigma2);
    }

}
