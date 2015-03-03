#include "vtKernel.h"
#include "main.h"
#include "pstKernel.h"
#include "bstKernel.h"
#include "depTree.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <omp.h>
#include <sstream>
#include <map>
#include <boost/numeric/ublas/matrix.hpp>

using namespace std;
using namespace boost::numeric::ublas;

std::string PATH = "/home/kim/xresearch/";

// Index where the flag value changes
map <string, int> MID_POINTS
{
    {"sentiment", 5331},
    {"metaphor", 1385},
    {"subjectivity", 5000},
    {"books", 997}
};

int main(int argc, char* argv[])
{

    std::vector<string> sets;
    string dataset(argv[1]);
    cout << dataset << endl;

    string ipath = PATH + "data/" + dataset + "/";
    string opath = PATH + "result/" + dataset + "_kernel_matrix.csv";

    pstKernel model(ipath, 1, 5);
    auto graphs = loadGraphs(ipath);
    auto dts = loadDepTree(graphs);

    int n;

    if (argc==3)
      {
	n = atoi(argv[2]);
      }
    else if (argc==2) 
      {
	n = dts.size();
      }
    else 
      {
	throw std::invalid_argument("wrong number of arguments");
      }

    std::vector<int> indexset(n);
    if (argc==3)
      {    
	std::iota(indexset.begin(), indexset.end(), 0);
      }
    // Assign the index used for the kernel computation so that it can be balanced across flags
    else if (argc==2)
      {
	int mid_point = MID_POINTS[dataset];
	for (int i=0; i<n; i++)
	  {
	    std::iota(indexset.begin(), indexset.begin() + n/2, 0);
	    std::iota(indexset.begin() + n/2, indexset.end(), mid_point);
	  }
      }

    // Grpah kernel matrix
    matrix<double> kernel_matrix(n, n);

    int finished(0), prev(0);
    int total = (n*(n+1))/2;

    // Declare i and j in advance so that we can use static scheduling of OpenMP
    int i, j;

    #pragma omp parallel for private(j) schedule(static, 1)
    for (i=0; i<n; i++)
    {
        for (j=i; j<n; j++)
        {
            kernel_matrix(i, j) = model.sentenceKernel(dts[indexset.at(i)], dts[indexset.at(j)]);
            kernel_matrix(j, i) = kernel_matrix(i, j);
        }

        finished += n-i;
        int increment = int((finished - prev) * 100. / total);

        // Outputs the progress in percentage
        if (increment)
        {
            cout << int(finished * 100. / total) << "\% finished" << endl;
            prev = finished;
        }
    }

    writeToCsv(kernel_matrix, opath);

}
