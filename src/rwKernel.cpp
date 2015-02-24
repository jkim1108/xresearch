#include "rwKernel.h"
#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace Eigen;
using namespace std;

rwKernel::rwKernel(string ipath) : vtKernel(ipath)
/*
    Set the sentiment basis vector
*/
{
    _sent_vector = _embedding["good"] - _embedding["bad"];
}

double rwKernel::_sentimentKernel(string& word1, string& word2)
/*
    Laplacian kernel for the senitment similarity between two words
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
        return exp(-abs(diff.dot(_sent_vector)));
    }
};

double rwKernel::_wordKernel(string& word1, string& word2)
/*
    Actual word kernel used for the product adjacency matrix
*/
{
    return this->_sentimentKernel(word1, word2) * this->_lexicalKernel(word1, word2);
}

void rwKernel::_makeProductAdjMatrix(SparseMatrix <float> * adj_matrix, Graph* graph1, Graph* graph2)
/*
    Make an adjacency matrix for the product graph
*/
{
    int n1 = graph1->label_list.size();

    auto gl1 = graph1->label_list;
    auto gl2 = graph2->label_list;

    for (unsigned int i=0; i < graph1->label_list.size(); i++)
    {
        for (unsigned int j=0; j < graph2->label_list.size(); j++)
        {
            int ind = i + j * n1 + 1;
            adj_matrix->coeffRef(0, ind) = this->_wordKernel(gl1[i], gl2[j]);
        }
    }

    for (auto edge1 : graph1->edge_list)
    {
        for (auto edge2 : graph2->edge_list)
        {
            int ind1 = edge1.first + edge2.first * n1 + 1;
            int ind2 = edge1.second + edge2.second * n1 + 1;
            int ind3 = edge1.second + edge2.first * n1 + 1;
            int ind4 = edge1.first + edge2.second * n1 + 1;

            adj_matrix->coeffRef(ind2, ind1) = this->_wordKernel(gl1[edge1.first], gl2[edge2.first]);
            adj_matrix->coeffRef(ind1, ind2) = this->_wordKernel(gl1[edge1.second], gl2[edge2.second]);
            adj_matrix->coeffRef(ind4, ind3) = this->_wordKernel(gl1[edge1.second], gl2[edge2.first]);
            adj_matrix->coeffRef(ind3, ind4) = this->_wordKernel(gl1[edge1.first], gl2[edge2.second]);
        }
    }
}

double rwKernel::sentenceKernel(Graph* graph1, Graph* graph2)
/*
    Random walk kernel obtained from the common walks between graph1 and graph2
    using the product graph formulation
*/
{
    int n1 = graph1->label_list.size();
    int n2 = graph2->label_list.size();
    SparseMatrix<float> adj_matrix(n1*n2+1, n1*n2+1);
    this->_makeProductAdjMatrix(&adj_matrix, graph1, graph2);

    int walk_length = 3;
    double sum = diffusionKernel(adj_matrix, walk_length);

    return sum;
}

