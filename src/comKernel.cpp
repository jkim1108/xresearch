#include "main.h"
#include "vtKernel.h"
#include "comKernel.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace Eigen;
using namespace std;

comKernel::comKernel(string ipath) : vtKernel(ipath) {};

double comKernel::sentenceKernel(Graph* graph1, Graph* graph2)
/*
    Laplacian kernel from the distance of two centre of masses
*/
{
    auto vector1 = this->_centreOfMass(graph1);
    auto vector2 = this->_centreOfMass(graph2);

    auto diff = vector1 - vector2;

    return exp(-.1 * diff.norm());
};

VectorXd comKernel::_centreOfMass(Graph* graph)
/*
    Outputs the center of mass of the given graph ignoring words without embeddings
*/
{
    VectorXd res(300);
    int n = 0;

    for (auto label:graph->label_list)
    {
        VectorXd vec = _embedding[label];
        if (vec.size())
        {
            res += vec;
            n++;
        }
    }

    return res/n;
};
