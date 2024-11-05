#include "parse.hpp"

#include <iostream>
#include <utility>
#include <valarray>
#include <vector>

#include "graph.hpp"

namespace GeneticTSP
{

namespace
{

int manhattan_distance(coordinate_type a, coordinate_type b)
{
    return std::abs(a.first - b.first) + std::abs(a.second + b.second);
}

} // namespace

std::vector<coordinate_type> parse_coordinates(std::ifstream &fin)
{
    std::vector<coordinate_type> coordinates;

    int x, y;

    while (fin >> x >> y)
    {
        coordinates.emplace_back(x, y);
    }

    return coordinates;
}

Graph graph_from_coordinates(std::vector<coordinate_type> coordinates)
{
    Graph graph(coordinates.size());

    for (size_t i = 0; i < coordinates.size(); i++)
    {
        graph.adjacency_matrix[i][i] = 0;
        for (size_t j = i + 1; j < coordinates.size(); j++)
        {
            graph.adjacency_matrix[i][j] = graph.adjacency_matrix[j][i] =
                manhattan_distance(coordinates[i], coordinates[j]);
        }
    }

    return graph;
}

} // namespace GeneticTSP
