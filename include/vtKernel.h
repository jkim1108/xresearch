#ifndef VTKERNEL_H
#define VTKERNEL_H

#include "main.h"
#include "depTree.h"

#include <iostream>
#include <unordered_map>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

class vtKernel
/*
    Wrapper for the kernels using the dependency trees
*/
{
    public :
        vtKernel(Options opt);
        virtual double docKernel(const Graph* graph1, const Graph* graph2)=0;
        virtual double docKernel(const depTree* graph1, const depTree* graph2);
        double docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);
        double docKernel(std::vector<depTree*> doc1, std::vector<depTree*> doc2);
        //~vtKernel();

    protected :
        inline double _wordKernel(const string& word1, const string& word2)
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
            return _wordKernel(emb1, emb2);
        };

        inline double _wordKernel(const VectorXd& emb1, const VectorXd& emb2)
        {
            if (!emb1.size() || !emb2.size())
            {
                return 0.;
            }
            else
            {
                double cosSim = emb1.dot(emb2)/(emb1.norm() * emb2.norm());
                return std::pow(0.5*(cosSim + 1), _sigma);
            }
        };

        double _deltaKernel(const string& word1, const string& word2);

        unordered_map <string, VectorXd> _embedding;
        double _lambda;
        int _maxLength;
        double _sigma;
};

#endif // VTKERNEL_H
