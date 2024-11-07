#include "selector.hpp"

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

#include "path.hpp"

namespace GeneticTSP
{

std::vector<size_t>
BestFirstSelection::select_reproduce(const std::vector<Path>   &paths,
                                     const std::vector<size_t> &to_delete)
{
    using std::size;

    std::vector<bool>   eliminated_lookup(size(paths), false);
    std::vector<size_t> to_reproduce(size(to_delete));

    for (const auto ele : to_delete)
    {
        eliminated_lookup[ele] = true;
    }

    size_t curr_reproduction_index = 0;

    while (eliminated_lookup[curr_reproduction_index])
    {
        curr_reproduction_index++;
    }

    for (auto &ele : to_reproduce)
    {
        ele = curr_reproduction_index;

        while (eliminated_lookup[++curr_reproduction_index])
        {
        }
    }

    return to_reproduce;
}

FitnessUniformSelection::FitnessUniformSelection(
    std::random_device::result_type seed)
    : rng_engine(seed)
{
}

std::vector<size_t>
FitnessUniformSelection::select_reproduce(const std::vector<Path>   &paths,
                                          const std::vector<size_t> &to_delete)
{
    using std::begin, std::end, std::size;

    std::vector<std::pair<Path::weight_type, size_t>> survivor_data(
        size(paths) - size(to_delete));
    std::vector<bool>   deleted_lookup(size(paths), false);
    std::vector<size_t> to_reproduce;

    for (const auto ele : to_delete)
    {
        deleted_lookup[ele] = true;
    }

    for (size_t i = 0; i < size(paths); i++)
    {
        if (deleted_lookup[i])
        {
            continue;
        }

        survivor_data[i] = std::make_pair(paths[i].total_weight(), i);
    }

    std::sort(begin(survivor_data), end(survivor_data));

    const Path::weight_type min_weight = survivor_data.front().first;
    const Path::weight_type max_weight = survivor_data.back().first;

    distribution_type distribution(min_weight, max_weight);

    for (size_t i = 0; i < size(to_delete); i++)
    {
        std::pair<Path::weight_type, size_t> to_find =
            std::make_pair(distribution(rng_engine), 0);

        const auto found_lower_bound =
            std::lower_bound(begin(survivor_data), end(survivor_data), to_find);
        const auto found_upper_bound =
            std::upper_bound(begin(survivor_data), end(survivor_data), to_find);

        if (to_find.first - found_lower_bound->first >
            found_upper_bound->first - to_find.first)
        {
            to_reproduce[i] = found_upper_bound->second;
        }
        else
        {
            to_reproduce[i] = found_lower_bound->second;
        }
    }

    return to_reproduce;
}

} // namespace GeneticTSP
