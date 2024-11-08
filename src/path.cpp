#include "path.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>

#include "graph.hpp"

namespace GeneticTSP
{

Path::Path(const Graph &graph)
{
    using std::begin, std::end, std::size;

    path.resize(size(graph.adjacency_matrix));
    std::iota(begin(path), end(path), 0);

    weights.resize(size(path) - 1);

    total_weight_ = 0;
    for (size_t i = 0; i < size(path) - 1; i++)
    {
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

Path::Path(const Graph &graph, const std::vector<size_t> &path_) : path(path_)
{
    using std::begin, std::end, std::size;

    assert(size(path) == size(graph.adjacency_matrix));

    weights.resize(size(path) - 1);

    total_weight_ = 0;
    for (size_t i = 0; i < size(path) - 1; i++)
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
    using std::size;

    assert(edge1 < size(path) && edge2 < size(path));

    if (edge1 == edge2)
        return;

    std::swap(path[edge1], path[edge2]);

    for (size_t i = std::max<size_t>(edge1, 1) - 1;
         i <= std::min<size_t>(edge1 + 2, size(path)) - 2; i++)
    {
        total_weight_ -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }

    for (size_t i = std::max<size_t>(edge2, 1) - 1;
         i <= std::min<size_t>(edge2 + 2, size(path)) - 2; i++)
    {
        total_weight_ -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

void Path::reverse_range(const Graph &graph, size_t edge1, size_t edge2)
{
    using std::begin, std::size;

    if (edge1 > edge2)
    {
        std::swap(edge1, edge2);
    }

    assert(edge1 <= size(path) && edge2 <= size(path));

    std::reverse(begin(path) + edge1, begin(path) + edge2);

    for (size_t i = std::max<size_t>(edge1, 1) - 1;
         i < std::min<size_t>(edge2 + 1, size(path)) - 1; i++)
    {
        total_weight_ -= weights[i];
        weights[i] = graph.adjacency_matrix[path[i]][path[i + 1]];
        total_weight_ += weights[i];
    }
}

std::string Path::to_string()
{
    using std::size;

    std::stringstream ss;

    for (size_t i = 0; i < size(path); i++)
    {
        ss << path[i];

        if (i != size(path) - 1)
        {
            ss << "->";
        }
    }

    return ss.str();
}

} // namespace GeneticTSP
