#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <random>

#include "graph.hpp"
#include "path.hpp"

namespace GeneticTSP
{

template <size_t simulation_size> class Simulation
{
    std::default_random_engine gen;
    std::uniform_int_distribution<std::default_random_engine::result_type>
        rng_mutation;
    std::uniform_int_distribution<std::default_random_engine::result_type>
        rng_elimination;

    void sort();
    void eliminate_and_mutate();
    void mutate_path(Path &path);

  public:
    std::array<Path, simulation_size> paths;
    Graph                             graph;

    Simulation(Graph graph, std::random_device rng_device);

    void step();
};

} // namespace GeneticTSP

namespace GeneticTSP
{

namespace
{

template <std::size_t... Is, typename T>
std::array<T, sizeof...(Is)> make_array_impl(const T &def,
                                             std::index_sequence<Is...>)
{
    return {{(static_cast<void>(Is), void(), def)...}};
}

template <std::size_t N, typename T> std::array<T, N> make_array(const T &def)
{
    return make_array_impl(def, std::make_index_sequence<N>());
}

} // namespace

template <size_t simulation_size>
Simulation<simulation_size>::Simulation(Graph graph_, std::random_device device)
    : gen(std::default_random_engine{device()}),
      rng_mutation(std::uniform_int_distribution<
                   std::default_random_engine::result_type>(
          0, graph_.adjacency_matrix.size() - 1)),
      rng_elimination(std::uniform_int_distribution<
                      std::default_random_engine::result_type>(0, 100)),
      paths(make_array<simulation_size>(Path(graph_))), graph(graph_)
{
    std::vector<size_t> path_data(graph.adjacency_matrix.size());
    std::iota(path_data.begin(), path_data.end(), 0);

    for (Path &path : paths)
    {
        std::shuffle(std::begin(path_data), std::end(path_data), gen);
        path = Path(graph, path_data);
    }
}

template <size_t simulation_size> void Simulation<simulation_size>::sort()
{
    std::sort(paths.begin(), paths.end());
}

template <size_t simulation_size>
void Simulation<simulation_size>::eliminate_and_mutate()
{
    std::vector<size_t>               eliminated_indices;
    std::array<bool, simulation_size> eliminated_lookup{false};
    size_t                            eliminated_count = 0;

    eliminated_indices.reserve(16);
    for (size_t i = paths.size() - 1; i >= paths.size() / 5; i--)
    {
        if (rng_elimination(gen) < 100 * i / paths.size() - 20)
        {
            eliminated_count++;
            eliminated_indices.push_back(i);
            eliminated_lookup[i] = true;
        }

        if (eliminated_count == simulation_size / 2)
        {
            break;
        }
    }

    size_t curr_reproduction_index = 0;

    for (const size_t eliminated_index : eliminated_indices)
    {
        paths[eliminated_index] = Path(paths[curr_reproduction_index]);
        mutate_path(paths[eliminated_index]);

        while (!eliminated_lookup[++curr_reproduction_index])
        {
        }
    }
}

template <size_t simulation_size>
void Simulation<simulation_size>::mutate_path(Path &path)
{
    path.swap_edges(graph, rng_mutation(gen), rng_mutation(gen));
}

template <size_t simulation_size> void Simulation<simulation_size>::step()
{
    eliminate_and_mutate();
    sort();
}

} // namespace GeneticTSP

#endif // #ifndef SIMULATION_HPP_INCLUDED
