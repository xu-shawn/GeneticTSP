#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <vector>

namespace GeneticTSP
{

class Graph;

class Path
{
    using weight_type = int32_t;

    weight_type              total_weight;
    std::vector<weight_type> weights;

  public:
    std::vector<size_t> path;

    explicit Path(const Graph &graph);
    Path(const Graph &graph, const std::vector<size_t> &path_);
    Path(const Path &other_path);

    void swap_edges(const Graph &graph, size_t edge1, size_t edge2);

    bool operator<(const Path &other) const
    {
        return total_weight < other.total_weight;
    }
};

} // namespace GeneticTSP

#endif // #ifndef PATH_HPP_INCLUDED
