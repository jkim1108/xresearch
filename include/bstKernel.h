#ifndef BSTKERNEL_H
#define BSTKERNEL_H

#include "main.h"
#include "vtKernel.h"
#include "depTree.h"

#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace boost::numeric;

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
            ublas::vector<double> baryCentre1;
            ublas::vector<double> baryCentre2;
            double value;
            double length;
        };

        bstKernel(string ipath, double lambda, int maxLength=0);
        friend std::ostream& operator<< (std::ostream& stream, const bstKernel& bk);
        double sentenceKernel(Graph* graph1, Graph* graph2);
        double sentenceKernel(depTree* dt1, depTree* dt2);

    protected:
        double C(Graph* graph1, Graph* graph2, unsigned int i, unsigned int j, int l, preComputed& pre);
        double C(depTree* dt1, depTree* dt2, int i, int j, int l, preComputed& pre);

        double _lambda;
        int _maxLength;

        inline ublas::vector<double> _updateBaryCentre(ublas::vector<double>& baryCentre, int length, ublas::vector<double>& newVector)
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
