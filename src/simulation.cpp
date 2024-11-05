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

Simulation::Simulation(Graph graph_, size_t size, std::random_device device,
                       std::unique_ptr<Terminator> &&terminator_,
                       std::unique_ptr<Selector>   &&selector_)
    : gen(std::default_random_engine{device()}),
      rng_mutation(std::uniform_int_distribution<
                   std::default_random_engine::result_type>(
          0, graph_.adjacency_matrix.size() - 1)),
      graph(graph_), terminator(std::move(terminator_)),
      selector(std::move(selector_))
{
    std::vector<size_t> path_data(graph.adjacency_matrix.size());
    std::iota(std::begin(path_data), std::end(path_data), 0);

    for (int i = 0; i < size; i++)
    {
        std::shuffle(std::begin(path_data), std::end(path_data), gen);
        paths.emplace_back(graph, path_data);
    }
}

void Simulation::sort()
{
    std::sort(std::begin(paths), std::end(paths));
}

void Simulation::eliminate_and_mutate()
{
    std::vector<size_t> eliminated_indices =
        terminator->generate_eliminations(this);
    std::vector<size_t> reproducing_indices =
        selector->select_reproduce(paths, eliminated_indices);

    assert(eliminated_indices.size() == reproducing_indices.size());

    for (int i = 0; i < eliminated_indices.size(); i++)
    {
        paths[eliminated_indices[i]] = Path(paths[reproducing_indices[i]]);
        mutate_path(paths[eliminated_indices[i]]);
    }
}

void Simulation::mutate_path(Path &path)
{
    path.swap_edges(graph, rng_mutation(gen), rng_mutation(gen));
}

void Simulation::step()
{
    eliminate_and_mutate();
    sort();
}

} // namespace GeneticTSP
