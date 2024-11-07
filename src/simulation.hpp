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

class Simulation
{
    std::default_random_engine gen;
    std::uniform_int_distribution<std::default_random_engine::result_type>
        rng_mutation;

    void sort();
    void eliminate_and_mutate(Terminator &terminator, Selector &selector);
    void mutate_path(Path &path);

  public:
    std::vector<Path> paths;
    Graph             graph;

    Simulation(Graph graph, size_t size, std::random_device::result_type seed);

    void step(Terminator &terminator, Selector &selector);
};

} // namespace GeneticTSP

#endif // #ifndef SIMULATION_HPP_INCLUDED
