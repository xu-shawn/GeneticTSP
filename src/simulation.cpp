#include "simulation.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <random>
#include <vector>

#include "graph.hpp"
#include "path.hpp"
#include "selector.hpp"
#include "terminator.hpp"

namespace GeneticTSP
{

Simulation::Simulation(Graph graph_, size_t sim_size, std::random_device device)
    : gen(std::default_random_engine{device()}),
      rng_mutation(std::uniform_int_distribution<
                   std::default_random_engine::result_type>(
          0, std::size(graph_.adjacency_matrix) - 1)),
      graph(graph_)
{
    using std::begin, std::end, std::size;

    std::vector<size_t> path_data(size(graph.adjacency_matrix));
    std::iota(begin(path_data), end(path_data), 0);

    for (int i = 0; i < sim_size; i++)
    {
        std::shuffle(begin(path_data), end(path_data), gen);
        paths.emplace_back(graph, path_data);
    }
}

void Simulation::sort()
{
    using std::begin, std::end;

    std::sort(begin(paths), end(paths));
}

void Simulation::eliminate_and_mutate(Terminator &terminator,
                                      Selector   &selector)
{
    using std::begin, std::end, std::size;

    std::vector<size_t> eliminated_indices =
        terminator.generate_eliminations(paths);
    std::vector<size_t> reproducing_indices =
        selector.select_reproduce(paths, eliminated_indices);

    assert(size(eliminated_indices) == size(reproducing_indices));

    for (int i = 0; i < size(eliminated_indices); i++)
    {
        paths[eliminated_indices[i]] = Path(paths[reproducing_indices[i]]);
        mutate_path(paths[eliminated_indices[i]]);
    }
}

void Simulation::mutate_path(Path &path)
{
    path.swap_edges(graph, rng_mutation(gen), rng_mutation(gen));
}

void Simulation::step(Terminator &terminator, Selector &selector)
{
    eliminate_and_mutate(terminator, selector);
    sort();
}

} // namespace GeneticTSP
