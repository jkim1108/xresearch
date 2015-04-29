#ifndef CompositeKernel_H
#define CompositeKernel_H

#include "main.h"
#include "Kernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>
#include <unordered_map>
#include <Eigen/Dense>

using namespace Eigen;

class CompositeKernel : public Kernel
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

        CompositeKernel(Options opt);
        double docKernel(const Graph* graph1, const Graph* graph2);
        double docKernel(const depTree* dt1, const depTree* dt2);

    protected:
        double C(const Graph* graph1, const Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        double C(const depTree* dt1, const depTree* dt2, int i, int j, int l, preComputed& pre);
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
                    return vector1.cwiseProduct(vector2);
                }
                else
                {
                    return vector1 + vector2;
                }
            }
        }
        bool _useMult;
        double _lambda2;

};

#endif // CompositeKernel_H
