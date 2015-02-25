#ifndef BSTKERNEL_H
#define BSTKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>

class bstKernel : public vtKernel
{
    public:
        struct preComputed
        {
            preComputed()
            {
                value = 0.;
                length = 0.;
            }
            VectorXd bariCentre1;
            VectorXd bariCentre2;
            double value;
            double length;
        };

        bstKernel(string ipath, double lambda);
        double sentenceKernel(Graph* graph1, Graph* graph2);
        double sentenceKernel(depTree* dt1, depTree* dt2);

    protected:
        double C(Graph* graph1, Graph* graph2, int i, int j, int l, preComputed& pre);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l);
        double _lambda;
        inline VectorXd _updateBariCentre(VectorXd bariCentre, int length, VectorXd newVector)
        {
            if ((length==0) || (bariCentre.size()==0))
            {
                return newVector;
            }
            else if (newVector.size()==0)
            {
                return bariCentre;
            }
            else
            {
                return (bariCentre * length + newVector)/(length + 1);
            }
        }
};

#endif // BSTKERNEL_H
