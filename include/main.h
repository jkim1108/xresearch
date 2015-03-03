#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>

#include <unordered_map>
#include <map>

using namespace std;
using namespace boost::numeric;

string PATH = "/home/kim/xresearch/";

// Index where the flag value changes
map <string, int> MID_POINTS
{
    {"sentiment", 5331},
    {"metaphor", 1385},
    {"subjectivity", 5000},
    {"books", 997}
};

struct Graph
/*
    Graph structure that has labels, edges, and flag(positive or negative) information
*/
{
    std::vector<string> labelList;
    std::vector<std::pair<int, int>> edgeList;
    bool flag;
};

// Utility functions
pair <int, int> vectorToPair(std::vector<int> input);
double factorial(int n);

// Functions dealing with IO's
std::vector<std::vector<Graph*>> load_doc_graphs(std::vector<Graph*> graphs);
std::vector<Graph*> loadGraphs(string path);
unordered_map<string, ublas::vector<double>> loadEmbedding(string path);
void writeToCsv(ublas::matrix<double>& kernel_matrix, string path);

#endif //MAIN_H
