#include "main.h"
#include "vtKernel.h"
#include "parser.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#include <Eigen/Dense>

using namespace Eigen;
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
    _useCoSim = opt.useCoSim;
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
double vtKernel::docKernel(const depTree* graph1, const depTree* graph2) {}

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
            res += this->docKernel(graph1, graph2);
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
            res += this->docKernel(dt1, dt2);
        }
    }
    return res;
}

double vtKernel::_deltaKernel(const string& word1, const string& word2)
/*
    Outputs the dirac delta kernel value between two words
*/
{
    return (word1 == word2);
}

double vtKernel::_lexicalKernel(const string& word1, const string& word2)
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

double vtKernel::_lexicalKernel(const VectorXd& emb1, const VectorXd& emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 0.;
    }
    else
    {
        if (_useCoSim)
        {
            double cosSim = emb1.dot(emb2)/(emb1.norm() * emb2.norm());
            return std::pow(0.5*(cosSim + 1), _sigma1);
        }
        else
        {
            auto diff = emb1 - emb2;
            return exp(-diff.norm()/_sigma1);
        }
    }
}

double vtKernel::_sentimentKernel(const string& word1, const string& word2)
{
    if (word1 == word2)
    {
        return 1.;
    }
    auto emb1 = _embedding[word1];
    auto emb2 = _embedding[word2];
    return _sentimentKernel(emb1, emb2);
}

double vtKernel::_sentimentKernel(const VectorXd& emb1, const VectorXd& emb2)
{
    if (!emb1.size() || !emb2.size())
    {
        return 1.;
    }
    else
    {
        VectorXd diff = emb1 - emb2;
        return exp(-abs(diff.dot(_sent_vector))/_sigma2);
    }
}
