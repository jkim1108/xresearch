#include "main.h"
#include "Kernel.h"
#include "parser.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

Kernel::Kernel(Options opt)
/*
    Assign the embedding dictionary and sentiment vector which shall be used for
    the computation of the kernel
*/
{
    _embedding = loadEmbedding(getInputPath(opt.dataset));
    _lambda1 = opt.lambda1;
    _maxLength = opt.maxLength;
    string PATH = "/home/kim/xresearch/";
    _alpha = opt.alpha;
}

double Kernel::docKernel(const depTree* graph1, const depTree* graph2)
{
    throw std::runtime_error("Kernel undefiend for dependency tree");
    return 0.;
}

double Kernel::docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2)
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

double Kernel::docKernel(std::vector<depTree*> doc1, std::vector<depTree*> doc2)
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

double Kernel::_deltaKernel(const string& word1, const string& word2)
/*
    Outputs the dirac delta kernel value between two words
*/
{
    return (word1 == word2);
}

