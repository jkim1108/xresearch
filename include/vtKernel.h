#ifndef VTKERNEL_H
#define VTKERNEL_H

#include "main.h"

#include <iostream>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

using namespace std;
using namespace Eigen;

class vtKernel{
    /*
        Wrapper for the kernels using the dependency trees
    */

    public :

        vtKernel(string ipath);
        virtual double sentenceKernel(Graph * graph1, Graph * graph2)=0;
        double doc_kernel(std::vector<Graph*> doc1, std::vector<Graph*> doc2);

        //~vtKernel();

    protected :

        unordered_map <string, VectorXd> _embedding;

};


#endif // VTKERNEL_H
