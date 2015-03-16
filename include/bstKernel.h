#ifndef BSTKERNEL_H
#define BSTKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <Eigen/Dense>

using namespace Eigen;

class bstKernel : public vtKernel
/*
    Baricentric Subtree Kernel
*/
{
    public:
        struct preComputed
        {
            preComputed()
            {
                value = 0.;
                length = 0.;
            }
            VectorXd baryCentre1;
            VectorXd baryCentre2;
            double value;
            int length;
        };

        bstKernel(Options opt);
        double docKernel(Graph* graph1, Graph* graph2);
        double docKernel(depTree* dt1, depTree* dt2);

    protected:
        virtual double C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        virtual double C(depTree* dt1, depTree* dt2, int i, int j, int l, preComputed& pre);
        inline VectorXd _updateBaryCentre(VectorXd& baryCentre, int length, VectorXd& newVector)
        {
            if ((length==0) || (baryCentre.size()==0))
            {
                return newVector;
            }
            else if (newVector.size()==0)
            {
                return baryCentre;
            }
            else
            {
                return (baryCentre * length + newVector)/(length + 1);
            }
        }
};

#endif // BSTKERNEL_H
