#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace GeneticTSP
{

class Graph;

class Path
{
  public:
    using weight_type = int32_t;

  private:
    weight_type              total_weight_;
    std::vector<weight_type> weights;

  public:
    std::vector<size_t> path;

    explicit Path(const Graph &graph);
    Path(const Graph &graph, const std::vector<size_t> &path_);
    Path(const Path &other_path);

    void        swap_edges(const Graph &graph, size_t edge1, size_t edge2);
    void        reverse_range(const Graph &graph, size_t edge1, size_t edge2);
    std::string to_string();

    weight_type total_weight() const
    {
        return total_weight_;
    }

    bool operator<(const Path &other) const
    {
        return total_weight_ < other.total_weight_;
    }
};

} // namespace GeneticTSP

#endif // #ifndef PATH_HPP_INCLUDED
