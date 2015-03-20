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
        {
            if (not _useSent)
            {
                return _lexicalKernel(word1, word2);
            }
            else
            {
                return _lexicalKernel(word1, word2) * _sentimentKernel(word1, word2);
            }
        };

        inline double _wordKernel(const VectorXd& emb1, const VectorXd& emb2)
        {
            if (not _useSent)
            {
                return _lexicalKernel(emb1, emb2);
            }
            else
            {
                return _lexicalKernel(emb1, emb2) * _sentimentKernel(emb1, emb2);
            }
        };

        double _lexicalKernel(const string& word1, const string& word2);
        double _lexicalKernel(const VectorXd& emb1, const VectorXd& emb2);

        double _sentimentKernel(const string& word1, const string& word2);
        double _sentimentKernel(const VectorXd& emb1, const VectorXd& emb2);

        double _deltaKernel(const string& word1, const string& word2);

        unordered_map <string, VectorXd> _embedding;
        double _lambda;
        int _maxLength;
        bool _useSent;
        bool _useSWN;
        bool _useCoSim;
        VectorXd _sent_vector;
        double _sigma1;
        double _sigma2;
};

#endif // VTKERNEL_H
