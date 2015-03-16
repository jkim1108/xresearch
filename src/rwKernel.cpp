#include "rwKernel.h"
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <Eigen/SparseCore>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

rwKernel::rwKernel(Options opt) :
                    vtKernel(opt)
                    {}

void rwKernel::_makeProductAdjMatrix(SparseMatrix<double>& adjMatrix, Graph* graph1, Graph* graph2)
/*
    Make an adjacency matrix for the product graph
*/
{
    int n1 = graph1->labelList.size();

    auto gl1 = graph1->labelList;
    auto gl2 = graph2->labelList;

    for (unsigned int i=0; i < graph1->labelList.size(); i++)
    {
        for (unsigned int j=0; j < graph2->labelList.size(); j++)
        {
            int ind = i + j * n1 + 1;
            adjMatrix.coeffRef(0, ind) = this->_wordKernel(gl1[i], gl2[j]);
        }
    }

    for (auto edge1 : graph1->edgeList)
    {
        for (auto edge2 : graph2->edgeList)
        {
            int ind1 = edge1.first + edge2.first * n1 + 1;
            int ind2 = edge1.second + edge2.second * n1 + 1;
            int ind3 = edge1.second + edge2.first * n1 + 1;
            int ind4 = edge1.first + edge2.second * n1 + 1;
            adjMatrix.coeffRef(ind2, ind1) = this->_wordKernel(gl1[edge1.first], gl2[edge2.first]);
            adjMatrix.coeffRef(ind1, ind2) = this->_wordKernel(gl1[edge1.second], gl2[edge2.second]);
            adjMatrix.coeffRef(ind4, ind3) = this->_wordKernel(gl1[edge1.second], gl2[edge2.first]);
            adjMatrix.coeffRef(ind3, ind4) = this->_wordKernel(gl1[edge1.first], gl2[edge2.second]);
        }
    }
}

double rwKernel::docKernel(Graph* graph1, Graph* graph2)
/*
    Random walk kernel obtained from the common walks between graph1 and graph2
    using the product graph formulation
*/
{
    int n1 = graph1->labelList.size();
    int n2 = graph2->labelList.size();
    SparseMatrix<double> adjMatrix(n1*n2+1, n1*n2+1);
    this->_makeProductAdjMatrix(adjMatrix, graph1, graph2);

    auto accMatrix(adjMatrix);
    int i = 0;

    double sum = _lambda * adjMatrix.row(0).sum();
    while(++i<_maxLength)
    {
        accMatrix = accMatrix * adjMatrix;
        sum += accMatrix.row(0).sum() / factorial(i);
    }

    return sum;
}
