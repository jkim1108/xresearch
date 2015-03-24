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
            VectorXd compVector1;
            VectorXd compVector2;
            double value=0.;
            int length=0;
        };

        bstKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* dt1, const depTree* dt2);

    protected:
        virtual double C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        virtual double C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre);
        bool _useMult;
        inline VectorXd _updateComposition(VectorXd& vector1, VectorXd& vector2, int length)
        {
            if (length==0)
            {
                return vector2;
            }
            else if (vector1.size()==0 or vector2.size()==0)
            {
                VectorXd null;
                return null;
            }
            else
            {
                if (_useMult)
                {
                    return (vector1 * vector2);
                }
                else
                {
                    return vector1 + vector2;
                }
            }
        }

};

#endif // BSTKERNEL_H
