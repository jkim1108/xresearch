#include "main.h"
#include "rwKernel.h"
#include "comKernel.h"

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

std::string PATH = "/home/jonghoon/polytechnique/python/";

// Index where the flag value changes
map <string, int> MID_POINTS
{
    {"sentiment", 5331},
    {"metaphor", 1385},
    {"subjectivity", 5000},
    {"books", 997}
};

int main()
{
    int n = 300;
    std::vector<string> sets;
    string dataset = "sentiment";
    cout << dataset << endl;

    string ipath = PATH + "data/" + dataset + "/";
    string opath = PATH + dataset + "_kernel_matrix.csv";

    rwKernel model(ipath);
    auto graphs = loadGraphs(ipath);

    std::vector<int> indexset(n);
    int mid_point = MID_POINTS[dataset];

    // Assign the index used for the kernel computation so that it can be balanced across flags
    for (int i=0; i<n; i++)
    {
        if (i<n/2)
        {
            indexset.at(i) = i;
        }
        else
        {
            indexset.at(i) = mid_point + i - n/2;
        }
    }

    // Grpah kernel matrix
    matrix<double> kernel_matrix(n, n);

    int finished, prev;
    int total = (n*(n+1))/2;

    // Declare i and j in advance so that we can use static scheduling of OpenMP
    int i, j;

    #pragma omp parallel for private(j) schedule(static, 1)
    for (i=0; i<n; i++)
    {
        for (j=i; j<n; j++)
        {
            kernel_matrix(i, j) = model.sentenceKernel(graphs[indexset.at(i)], graphs[indexset.at(j)]);
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
