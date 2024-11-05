#include "selector.hpp"

#include "path.hpp"

namespace GeneticTSP
{

std::vector<size_t>
BestFirstSelection::select_reproduce(const std::vector<Path>   &paths,
                                     const std::vector<size_t> &to_delete) const
{
    std::vector<bool>   eliminated_lookup(paths.size(), false);
    std::vector<size_t> to_reproduce(to_delete.size());

    for (const auto ele : to_delete)
    {
        eliminated_lookup[ele] = true;
    }

    size_t curr_reproduction_index = 0;

    while (!eliminated_lookup[curr_reproduction_index])
    {
        curr_reproduction_index++;
    }

    for (auto &ele : to_reproduce)
    {
        ele = curr_reproduction_index;

        while (!eliminated_lookup[++curr_reproduction_index])
        {
        }
    }

    return to_reproduce;
}

} // namespace GeneticTSP
