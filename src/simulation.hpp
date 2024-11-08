#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <random>

#include "graph.hpp"
#include "path.hpp"

namespace GeneticTSP
{

struct Terminator;
struct Selector;
struct Mutator;

class Simulation
{
    void sort();
    void eliminate_and_mutate(Terminator &terminator, Selector &selector,
                              Mutator &mutator);

  public:
    std::vector<Path> paths;
    Graph             graph;

    Simulation(Graph graph, size_t size, std::random_device::result_type seed);

    void step(Terminator &terminator, Selector &selector, Mutator &mutator);
};

} // namespace GeneticTSP

#endif // #ifndef SIMULATION_HPP_INCLUDED
