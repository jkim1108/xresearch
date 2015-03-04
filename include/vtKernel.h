#ifndef VTKERNEL_H
#define VTKERNEL_H

#include "main.h"
#include "depTree.h"

#include <iostream>
#include <unordered_map>

using namespace std;
using namespace boost::numeric;

class vtKernel
/*
    Wrapper for the kernels using the dependency trees
*/
{
    public :
        vtKernel(string ipath, double lambda, int maxLength, bool useSent=false);
        virtual double sentenceKernel(Graph* graph1, Graph* graph2)=0;
        virtual double sentenceKernel(depTree* graph1, depTree* graph2);
        double docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);
        //~vtKernel();

    protected :
        double _wordKernel(string& word1, string& word2);
        double _lexicalKernel(string& word1, string& word2);
        double _sentimentKernel(string& word1, string& word2);
        double _deltaKernel(string& word1, string& word2);
        double _laplacianKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2, double sigma);

        unordered_map <string, ublas::vector<double>> _embedding;
        double _lambda;
        int _maxLength;
        bool _useSent;
        ublas::vector<double> _sent_vector;
};

#endif // VTKERNEL_H
