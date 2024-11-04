#include "simulation.hpp"

#include "path.hpp"
#include <algorithm>

namespace GeneticTSP
{

template <size_t simulation_size>
Simulation<simulation_size>::Simulation(Graph graph_) : graph(graph_)
{
    paths.fill(Path(graph));
}

template <size_t simulation_size> void Simulation<simulation_size>::sort()
{
    std::sort(paths.begin(), paths.end());
}

} // namespace GeneticTSP
