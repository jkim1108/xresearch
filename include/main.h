#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>

#include <Eigen/Dense>
#include <Eigen/SparseCore>
#include <unordered_map>
#include <map>

using namespace std;
using namespace Eigen;
using namespace boost::numeric::ublas;

struct Graph
/*
    Graph structure that has labels, edges, and flag(positive or negative) information
*/
{
    std::vector<string> label_list;
    std::vector<std::pair<int, int>> edge_list;
    bool flag;
};

// Utility functions
pair <int, int> vectorToPair(std::vector<int> input);
double factorial(int n);
double diffusionKernel(SparseMatrix <float>& adj_matrix, int n);

// Functions dealing with IO's
std::vector<std::vector<Graph*>> load_doc_graphs(std::vector<Graph*> graphs);
std::vector<Graph*> loadGraphs(string path);
unordered_map <string, VectorXd> loadEmbedding(string path);
void writeToCsv(matrix<double>& kernel_matrix, string path);


#endif //MAIN_H
