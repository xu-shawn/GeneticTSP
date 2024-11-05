#include "graph.hpp"
#include <vector>

namespace GeneticTSP
{

Graph::Graph(adjacency_matrix_type adj_matrix) : adjacency_matrix(adj_matrix)
{
}

Graph::Graph(size_t size)
    : adjacency_matrix(std::vector<std::vector<weight_type>>(
          size, std::vector<weight_type>(size)))
{
}

} // namespace GeneticTSP
