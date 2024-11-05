#ifndef PARSE_HPP_INCLUDED
#define PARSE_HPP_INCLUDED

#include <fstream>
#include <vector>

namespace GeneticTSP
{

namespace
{

using coordinate_type = std::pair<int, int>;

}

class Graph;

std::vector<coordinate_type> parse_coordinates(std::ifstream &);
Graph graph_from_coordinates(std::vector<coordinate_type>);

} // namespace GeneticTSP

#endif // #ifndef PARSE_HPP_INCLUDED
