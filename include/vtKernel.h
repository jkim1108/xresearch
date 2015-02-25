#ifndef VTKERNEL_H
#define VTKERNEL_H

#include "main.h"

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace std;
using namespace Eigen;

class vtKernel
/*
    Wrapper for the kernels using the dependency trees
*/
{
    public :
        vtKernel(string ipath);
        virtual double sentenceKernel(Graph* graph1, Graph* graph2)=0;
        double docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);
        //~vtKernel();

    protected :
        double _lexicalKernel(string& word1, string& word2);
        double _deltaKernel(string& word1, string& word2);
        double _laplacianKernel(VectorXd emb1, VectorXd emb2);
        unordered_map <string, VectorXd> _embedding;
};


#endif // VTKERNEL_H
