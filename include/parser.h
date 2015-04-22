#ifndef PARSER_H
#define PARSER_H

#include "vtKernel.h"
#include "bstKernel.h"
#include "strKernel.h"
#include "rwKernel.h"
#include "vstKernel.h"
#include "pstKernel.h"
#include "bKernel.h"

#include "main.h"

using namespace std;

vtKernel* kernelChooser(Options opt);
Options getOptions(string paramFile);
std::vector<int> getIndexSet(Options opt, int dataSize);
string getInputPath(string dataset);
string getOutputPath(string dataset);

template <typename T>
ublas::matrix<double> getPartialKernelMatrix(vtKernel* model, std::vector<T> testset, int rowStart, int rowEnd)
{
    int n = testset.size();
    int m = rowEnd - rowStart;
    
    ublas::matrix<double> kernelMatrix(m, n);

    int finished(0), prev(0);
    int total = m;
    int i, j;

    #pragma omp parallel for private(j) schedule(static, 1)
    for (i=0; i<m; i++)
    {
        for (j=0; j<n; j++)
        {
            kernelMatrix(i, j) = model->docKernel(testset[i + rowStart], testset[j]);
        }
        finished++;
        int increment = int((finished - prev) * 100. / total);

        if (increment)
        {
            cout << static_cast<int>(finished * 100. / total) << "\% finished" << endl;
            prev = finished;
        }
    }
    return kernelMatrix;
}


template <typename T>
ublas::matrix<double> getKernelMatrix(vtKernel* model, std::vector<T> testset)
{
    int n = testset.size();

    ublas::matrix<double> kernelMatrix(n, n);

    int finished(0), prev(0);
    int total = (n*(n+1))/2;
    int i, j;

    #pragma omp parallel for private(j) schedule(static, 1)
    for (i=0; i<n; i++)
    {
        for (j=i; j<n; j++)
        {
            kernelMatrix(i, j) = model->docKernel(testset[i], testset[j]);
            kernelMatrix(j, i) = kernelMatrix(i, j);
        }

        finished += n-i;
        int increment = int((finished - prev) * 100. / total);

        if (increment)
        {
            cout << int(finished * 100. / total) << "\% finished" << endl;
            prev = finished;
        }
    }
    return kernelMatrix;
}

template <typename T>
ublas::matrix<double> getKernelDiagonal(vtKernel* model, std::vector<T> testset)
{
    int n = testset.size();

    // Grpah kernel matrix
    ublas::matrix<double> kernelMatrix(n, 1);

    int i;
    //#pragma omp parallel
    for (i=0; i<n; i++)
    {
        kernelMatrix(i, 0) = model->docKernel(testset[i], testset[i]);
    }
    return kernelMatrix;
}



#endif // PARSER_H
