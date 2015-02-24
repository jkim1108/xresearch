#include "main.h"
#include "depTree.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

int height(map<int, std::vector<int>> children_map, int node_ind)
/*
    Find the height of the node from the bttom when given the map of children in the graphs
*/
{
    if (children_map.find(node_ind) == children_map.end())
    {
        return 0;
    }

    else
    {
        std::vector<int> children = children_map[node_ind];
        std::vector<int> heights(children.size());

        auto bind_height = std::bind(height, children_map, placeholders::_1);
        std::transform(children.begin(), children.end(), heights.begin(), bind_height);
        auto it = std::max_element(heights.begin(), heights.end());
        return *it+ 1;
    }
}

depTree::depTree(Graph* graph)
{
    map<int, std::vector<int>> children_map;
    for (auto edge:graph->edge_list)
    {
        if (children_map.find(edge.second)==children_map.end())
        {
            std::vector<int> child(1, edge.first);
            children_map[edge.second] = child;
        }
        else
        {
            children_map[edge.second].push_back(edge.first);
        }
    }

    int n = graph->label_list.size();
    std::vector<int> height_list(n);
    std::vector<int> range(n);
    std::iota(range.begin(), range.end(), 0);

    auto bind_height = std::bind(height, children_map, placeholders::_1);
    std::transform(range.begin(), range.end(), height_list.begin(), bind_height);

    for (int i=0; i<n; i++)
    {
        Node* node = new Node;
        node->label = graph->label_list[i];
        node->height = height_list[i];
        node->children = children_map[i];
        node_list.push_back(node);
    }
};


std::vector<depTree*> loadDepTree(std::vector<Graph*> graphs)
/*
    Helper function converting the vec of Graphs to vec of depTrees
*/
{
    std::vector<depTree*> output;
    for (int i=0; i<graphs.size(); i++)
    {
        depTree* dt = new depTree(graphs[i]);
        output.push_back(dt);
    }
    return output;
}
