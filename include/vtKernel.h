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
        vtKernel(Options opt);
        virtual double docKernel(Graph* graph1, Graph* graph2)=0;
        virtual double docKernel(depTree* graph1, depTree* graph2);
        double docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);
        double docKernel(std::vector<depTree*> doc1, std::vector<depTree*> doc2);
        //~vtKernel();

    protected :
        inline double _wordKernel(string& word1, string& word2)
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

        inline double _wordKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2)
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

        double _lexicalKernel(string& word1, string& word2);
        double _lexicalKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2);

        double _sentimentKernel(string& word1, string& word2);
        double _sentimentKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2);

        double _deltaKernel(string& word1, string& word2);

        unordered_map <string, ublas::vector<double>> _embedding;
        double _lambda;
        int _maxLength;
        bool _useSent;
        bool _useSWN;
        ublas::vector<double> _sent_vector;
        double _sigma1;
        double _sigma2;
};

#endif // VTKERNEL_H
