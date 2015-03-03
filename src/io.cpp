#include "main.h"

#include <iostream>
#include <fstream>

#include <boost/numeric/ublas/matrix.hpp>
#include <unordered_map>

using namespace std;
using namespace boost::numeric;

std::vector<std::vector<Graph*>> getDocGraphs(std::vector<Graph*> graphs)
/*
    Group graphs for the same documents
*/
{
    std::vector<std::vector<Graph*>> res;
    std::vector<Graph*> doc_graph;

    for (auto graph : graphs){
        string first = graph->labelList[0];
        if (first.find("###")==0)
        {
            res.push_back(doc_graph);
            doc_graph.clear();
        }
        else
        {
            doc_graph.push_back(graph);
        }
    }
    return res;
}

std::vector<Graph*> loadGraphs(string path)
/*
    Construct graphs from label/edge files
*/
{
    map<bool, std::vector<string>> filedic;
    std::vector<string> pos, neg;

    pos.push_back(path + "labels.pos");
    pos.push_back(path + "edges.pos");

    neg.push_back(path + "labels.neg");
    neg.push_back(path + "edges.neg");

    filedic[true] = pos;
    filedic[false] = neg;

    std::vector<std::vector <string>> wordset;
    std::vector<std::vector<pair<int, int>>> edgeset;
    std::vector<bool> flagset;


    for (auto flag:{ true, false })
    {
        std::ifstream infile(filedic[flag][0]);
        std::string line;
        while (infile.good())
        {
            string word;
            std::vector<string> words;
            getline(infile, line);
            std::stringstream linestream(line);
            while (getline(linestream, word, ';'))
            {
                words.push_back(word);
            }
            wordset.push_back(words);
            flagset.push_back(flag);
        }

        std::ifstream infile2(filedic[flag][1]);
        while (infile2.good())
        {
            string edge;
            std::vector<pair<int, int>> edges;
            getline(infile2, line);
            std::stringstream linestream(line);
            while (getline(linestream, edge, ','))
            {
                std::stringstream edgestream(edge);
                std::vector<int> index(0);
                string temp;
                while (getline(edgestream, temp,'-'))
                {
                    try
                    {

                        index.push_back(stoi(temp));
                    }
                    catch(std::invalid_argument)
                    {
//                        break;
                    }
                }
                if (index.size() == 2)
                {
                    edges.push_back(vectorToPair(index));
                }
            }
            edgeset.push_back(edges);
        }

        wordset.pop_back();
        edgeset.pop_back();
        flagset.pop_back();
    }

    std::vector<Graph*> graphs;

    for (unsigned int i=0; i<flagset.size(); i++)
    {
        Graph* graph = new Graph;
        graph->labelList = wordset[i];
        graph->edgeList = edgeset[i];
        graph->flag = flagset[i];
        graphs.push_back(graph);
    }

    return graphs;
};

unordered_map<string, ublas::vector<double>> loadEmbedding(string path)
/*
    Load word embeddings from the source files
*/
{
    std::vector<string> words;
    std::ifstream infile(path + "w2v_words.csv");
    string word;

    while (infile >> word)
    {
        words.push_back(word);
    }

    std::ifstream infile2(path + "w2v_embedding.csv");
    string line;

    std::vector<ublas::vector<double>> embeddings;
    while (infile2.good())
    {
        string temp;
        ublas::vector<double> embedding(300);
        getline(infile2, line);
        std::stringstream linestream(line);
        int ind = 0;

        while (getline(linestream, temp, ','))
        {
            embedding[ind] = std::stod(temp);
            ind++;
        }
        embeddings.push_back(embedding);
    }

    unordered_map <string, ublas::vector<double>> result;
    int n = words.size();
    for (int i=0; i<n; i++)
    {
        result[words[i]] = embeddings[i];
    }
    return result;

}

void writeToCsv(ublas::matrix<double>& kernel_matrix, string path)
/*
    Write the final output in numpy's to_csv format
*/
{
    int n = kernel_matrix.size1();
    ofstream ofile(path);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            ofile << kernel_matrix(i, j) << " ";
        }
        ofile << kernel_matrix(i, n-1) << endl;
    }
    ofile.close();
}
