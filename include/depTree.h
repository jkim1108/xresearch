#ifndef DEPTREE_H
#define DEPTREE_H

#include "main.h"

using namespace std;

struct depTree
/*
    Dependency tree structure for Subtree Kernel computation
*/
{
    public:
        struct Node
        /*
            Node structure for the dependency tree
        */
        {
            string label;
            int height;
            std::vector<int> children;
        };

        depTree(Graph* graph);
        std::vector<Node*> nodeList;
        int _maxHeight;
};

std::vector<depTree*> loadDepTree(std::vector<Graph*> graphs);
/*
    Helper function converting the vec of Graphs to vec of depTrees
*/

#endif // DEPTREE_H
