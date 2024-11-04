#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "graph.hpp"
#include "path.hpp"
#include <array>
#include <cstddef>

namespace GeneticTSP
{

template <size_t simulation_size> class Simulation
{
  public:
    std::array<Path, simulation_size> paths;
    Graph                             graph;

    Simulation(Graph graph);

    void sort();
};

} // namespace GeneticTSP

#endif // #ifndef SIMULATION_HPP_INCLUDED
