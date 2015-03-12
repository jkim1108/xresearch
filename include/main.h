#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <unordered_map>
#include <map>

using namespace std;
using namespace boost::numeric;

struct Graph
/*
    Graph structure that has labels, edges, and flag(positive or negative) information
*/
{
    std::vector<string> labelList;
    std::vector<std::pair<int, int>> edgeList;
    bool flag;
};

struct Options
{
    string dataset;
    string kernelType;
    double lambda;
    int maxLength;
    int dataSize;
    bool useDT;
    bool useSent;
    bool useSWN;
    double sigma1;
    double sigma2;
};

// Utility functions
pair <int, int> vectorToPair(std::vector<int> input);
double factorial(int n);

// Functions dealing with IO's
std::vector<std::vector<Graph*>> getDocGraphs(std::vector<Graph*> graphs);
std::vector<Graph*> loadGraphs(string path);
unordered_map<string, ublas::vector<double>> loadEmbedding(string path);
ublas::vector<double> loadSentVec(string path);
void writeToCsv(ublas::matrix<double>& kernelMatrix, string path);

#endif //MAIN_H
