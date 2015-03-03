#ifndef VTKERNEL_H
#define VTKERNEL_H

#include "main.h"

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
        vtKernel(string ipath);
        virtual double sentenceKernel(Graph* graph1, Graph* graph2)=0;
        double docKernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);
        //~vtKernel();

    protected :
        double _lexicalKernel(string& word1, string& word2);
        double _deltaKernel(string& word1, string& word2);
        double _laplacianKernel(ublas::vector<double>& emb1, ublas::vector<double>& emb2);
        unordered_map <string, ublas::vector<double>> _embedding;
};


#endif // VTKERNEL_H
