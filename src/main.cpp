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

using namespace std;
using namespace boost::numeric;

int main(int argc, char* argv[])
{
    auto t1 = clock();
    Options opt = getOptions(argv[1]);
    string ipath = getInputPath(opt.dataset);
    string opath = getOutputPath(argv[1]);
    
    cout << opt.dataset << endl;
    vtKernel* model = kernelChooser(opt);
    auto graphs = loadGraphs(ipath);
    if (opt.useDT)
    {
        auto dts = loadDepTree(graphs);
        auto testset = getTestSet<depTree*>(opt, dts);
        auto kernelMatrix = getKernelMatrix<depTree*>(model, testset);
        writeToCsv(kernelMatrix, opath);
    }
    else
    {
        auto testset = getTestSet<Graph*>(opt, graphs);
        auto kernelMatrix = getKernelMatrix<Graph*>(model, testset);
        writeToCsv(kernelMatrix, opath);
    }
    auto t2 = clock();
    std::cout << "finished in " << int(t2-t1)/CLOCKS_PER_SEC << " seconds" << endl;
}
