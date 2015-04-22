#include "vtKernel.h"
#include "main.h"
#include "parser.h"
#include "pstKernel.h"
#include "bstKernel.h"
#include "rwKernel.h"
#include "bKernel.h"
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
    int rowStart(stoi(string(argv[2])));
    int rowEnd(stoi(string(argv[3])));
    
    string ipath = getInputPath(opt.dataset);
    string opath = getOutputPath(argv[1]) + "_" + string(argv[2]) + "_" + string(argv[3]) + ".csv";
    
    std::vector<string> docList({"books", "kitchen_housewares", "dvd", "electronics", "plv2"});
    bool useDoc = std::find(docList.begin(), docList.end(), opt.dataset)!=docList.end();

    vtKernel* model = kernelChooser(opt);
    auto graphs = loadGraphs(ipath);
    cout << graphs.size() << endl;

    if (useDoc)
    {
        auto docGraphs = getDocGraphs(graphs);
        if (opt.useDT)
        {
            auto docDTs = getDocDTs(docGraphs);
            auto kernelMatrix = getPartialKernelMatrix<std::vector<depTree*>>(model, docDTs, rowStart, rowEnd);
            writeToCsv(kernelMatrix, opath);
        }
        else
        {
            auto kernelMatrix = getPartialKernelMatrix<std::vector<Graph*>>(model, docGraphs, rowStart, rowEnd);
            writeToCsv(kernelMatrix, opath);
        }
    }
    else
    {
        if (opt.useDT)
        {
            auto dts = loadDepTree(graphs);
            auto kernelMatrix = getPartialKernelMatrix<depTree*>(model, dts, rowStart, rowEnd);
            writeToCsv(kernelMatrix, opath);
        }
        else
        {
            auto kernelMatrix = getPartialKernelMatrix<Graph*>(model, graphs, rowStart, rowEnd);
            writeToCsv(kernelMatrix, opath);
        }
    }
    auto t2 = clock();
    std::cout << "finished in " << int(t2-t1)/CLOCKS_PER_SEC << " seconds" << endl;
}
