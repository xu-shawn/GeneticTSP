#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace GeneticTSP
{

class Graph
{
    using weight_type           = int32_t;
    using adjacency_matrix_type = std::vector<std::vector<weight_type>>;

  public:
    adjacency_matrix_type adjacency_matrix;
    Graph(adjacency_matrix_type adj_matrix);
    Graph(size_t size);
};

} // namespace GeneticTSP

#endif
