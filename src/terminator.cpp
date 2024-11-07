#include "terminator.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <random>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include "path.hpp"

namespace GeneticTSP
{

FitnessProbablisticDeletion::FitnessProbablisticDeletion(
    std::random_device::result_type seed)
    : rng_engine(seed), rng_distrib{0, 100}
{
}

std::vector<size_t> FitnessProbablisticDeletion::generate_eliminations(
    const std::vector<Path> &ordered_population)
{
    using std::size;

    std::vector<size_t> eliminated_indices;

    for (size_t i = size(ordered_population) - 1;
         i >= size(ordered_population) / 5; i--)
    {
        if (rng_distrib(rng_engine) < 100 * i / size(ordered_population) - 20)
        {
            eliminated_indices.push_back(i);
        }

        if (size(eliminated_indices) == size(ordered_population) / 2)
        {
            break;
        }
    }

    return eliminated_indices;
}

std::vector<size_t> FitnessUniformDeletion::generate_eliminations(
    const std::vector<Path> &population)
{
    using std::begin, std::end, std::cbegin, std::cend, std::size;

    const size_t num_levels = static_cast<int>(std::sqrt(size(population)));

    std::vector<std::unordered_set<size_t>> fitness_levels(num_levels);
    std::vector<std::pair<size_t, size_t>>  fitness_count;
    std::vector<size_t> fitness_partial_difference(num_levels);

    const auto [min_path, max_path] =
        std::minmax_element(cbegin(population), cend(population));
    const size_t levels_range =
        (max_path->total_weight() - min_path->total_weight()) / num_levels;

    for (size_t i = 0; i < size(population); i++)
    {
        fitness_levels[std::min((population[i].total_weight() -
                                 min_path->total_weight()) /
                                    levels_range,
                                num_levels - 1)]
            .insert(i);
    }

    for (size_t i = 0; i < size(fitness_levels); i++)
    {
        fitness_count.emplace_back(size(fitness_levels[i]), i);
    }

    std::sort(begin(fitness_count), end(fitness_count));

    for (size_t i = 0; i + 1 < size(fitness_levels); i++)
    {
        fitness_partial_difference[i] =
            fitness_count[i].first - fitness_count[i + 1].first;
    }

    fitness_partial_difference.back() = fitness_count.back().first;

    size_t sum_deleted = 0;
    size_t delete_to   = 0;
    while (sum_deleted < size(population) / 3 &&
           delete_to < size(fitness_partial_difference) - 1)
    {
        sum_deleted += fitness_partial_difference[delete_to] * (delete_to + 1);
        delete_to++;
    }

    std::vector<size_t> to_delete;

    for (size_t i = 0; i <= delete_to; i++)
    {
        for (size_t j = 0;
             j < fitness_count[i].first - fitness_count[delete_to].first; j++)
        {
            auto &curr_fitness_rank = fitness_levels[fitness_count[i].second];
            auto  selected_element  = begin(curr_fitness_rank);
            to_delete.push_back(*selected_element);
            curr_fitness_rank.erase(selected_element);
        }
    }

    return to_delete;
}

} // namespace GeneticTSP
