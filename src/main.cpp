#include "vtKernel.h"
#include "main.h"
#include "parser.h"
#include "pstKernel.h"
#include "bstKernel.h"
#include "rwKernel.h"
#include "depTree.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <omp.h>
#include <sstream>
#include <map>
#include <time.h>
#include <boost/numeric/ublas/matrix.hpp>

#include <Eigen/Dense>
#include <Eigen/SparseCore>

using namespace std;
using namespace Eigen;
using namespace boost::numeric;

int main(int argc, char* argv[])
{
    auto t1 = clock();
    Options opt = getOptions(argv[1]);
    string ipath = getInputPath(opt.dataset);
    string opath = getOutputPath(argv[1]);
    std::vector<string> blitzer({"books", "kitchen_housewares", "dvd", "electronics"});
    bool useDoc = std::find(blitzer.begin(), blitzer.end(), opt.dataset)!=blitzer.end();

    cout << opt.dataset << endl;
    vtKernel* model = kernelChooser(opt);
    auto graphs = loadGraphs(ipath);
    if (useDoc)
    {
        auto docGraphs = getDocGraphs(graphs);
        if (opt.useDT)
        {
            auto docDTs = getDocDTs(docGraphs);
            auto kernelMatrix = getKernelMatrix<std::vector<depTree*>>(model, docDTs);
            writeToCsv(kernelMatrix, opath);
        }
        else
        {
            auto kernelMatrix = getKernelMatrix<std::vector<Graph*>>(model, docGraphs);
            writeToCsv(kernelMatrix, opath);
        }
    }
    else
    {
        if (opt.useDT)
        {
            auto dts = loadDepTree(graphs);
            auto kernelMatrix = getKernelMatrix<depTree*>(model, dts);
            writeToCsv(kernelMatrix, opath);
        }
        else
        {
            auto kernelMatrix = getKernelMatrix<Graph*>(model, graphs);
            writeToCsv(kernelMatrix, opath);
        }
    }
    auto t2 = clock();
    std::cout << "finished in " << int(t2-t1)/CLOCKS_PER_SEC << " seconds" << endl;
}
