#include "path.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <sstream>
#include <utility>

#include "graph.hpp"

namespace GeneticTSP
{

Path::Path(const Graph &graph)
{
    path.resize(graph.adjacency_matrix.size());
    std::iota(path.begin(), path.end(), 0);

    weights.resize(path.size() - 1);

    total_weight_ = 0;
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

Path::Path(const Graph &graph, const std::vector<size_t> &path_) : path(path_)
{
    assert(path.size() == graph.adjacency_matrix.size());

    weights.resize(path_.size() - 1);

    total_weight_ = 0;
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

Path::Path(const Path &other_path)
    : total_weight_(other_path.total_weight_), weights(other_path.weights),
      path(other_path.path)
{
}

void Path::swap_edges(const Graph &graph, size_t edge1, size_t edge2)
{
    assert(edge1 >= 0 && edge2 >= 0);
    assert(edge1 < path.size() && edge2 < path.size());

    if (edge1 == edge2)
        return;

    std::swap(path[edge1], path[edge2]);

    for (size_t i = std::max<size_t>(edge1 - 1, 0);
         i < std::min<size_t>(edge1, path.size() - 2); i++)
    {
        total_weight_ -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }

    for (size_t i = std::max<size_t>(edge2 - 1, 0);
         i < std::min<size_t>(edge2, path.size() - 2); i++)
    {
        total_weight_ -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

std::string Path::to_string()
{
    std::stringstream ss;

    for (int i = 0; i < path.size(); i++)
    {
        ss << path[i];

        if (i != path.size() - 1)
        {
            ss << "->";
        }
    }

    return ss.str();
}

} // namespace GeneticTSP
