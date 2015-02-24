#ifndef DEPTREE_H
#define DEPTREE_H

#include <main.h>

using namespace std;

struct Node
/*
    Node structure for the dependency tree
*/
{
    string label;
    int height;
    std::vector<int> children;
};

struct depTree
/*
    Dependency tree structure for Subtree Kernel computation
*/
{
    public:
        depTree(Graph* graph);
        std::vector<Node*> node_list;
};

std::vector<depTree*> loadDepTree(std::vector<Graph*> graphs);
/*
    Helper function converting the vec of Graphs to vec of depTrees
*/

#endif // DEPTREE_H
