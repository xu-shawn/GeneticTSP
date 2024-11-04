#include "path.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>

#include "graph.hpp"

namespace GeneticTSP
{

Path::Path(const Graph &graph) : graph(graph)
{
    path.resize(graph.adjacency_matrix.size());
    std::iota(path.begin(), path.end(), 0);

    weights.resize(path.size() - 1);

    total_weight = 0;
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight += weights[i];
    }
}

Path::Path(const Graph &graph, const std::vector<size_t> &path_)
    : path(path_), graph(graph)
{
    assert(path.size() == graph.adjacency_matrix.size());

    weights.resize(path_.size() - 1);

    total_weight = 0;
    for (size_t i = 0; i < path.size() - 1; i++)
    {
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight += weights[i];
    }
}

Path::Path(const Path &other_path)
    : weights(other_path.weights), path(other_path.path),
      total_weight(other_path.total_weight), graph(other_path.graph)
{
}

void Path::swap_edges(size_t edge1, size_t edge2)
{
    assert(edge1 >= 0 && edge2 >= 0);
    assert(edge1 < path.size() && edge2 < path.size());
    assert(edge1 != edge2);

    std::swap(path[edge1], path[edge2]);

    for (size_t i = std::max<size_t>(edge1 - 1, 0);
         i < std::min<size_t>(edge1, path.size() - 2); i++)
    {
        total_weight -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight += weights[i];
    }

    for (size_t i = std::max<size_t>(edge2 - 1, 0);
         i < std::min<size_t>(edge2, path.size() - 2); i++)
    {
        total_weight -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight += weights[i];
    }
}

} // namespace GeneticTSP
