#ifndef SELECTOR_HPP_INCLUDED
#define SELECTOR_HPP_INCLUDED

#include <vector>

namespace GeneticTSP
{

class Path;

struct Selector
{
    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) const = 0;
    virtual ~Selector()                                          = default;
};

struct BestFirstSelection : Selector
{
    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) const final override;
};

struct FitnessUniformSelection : Selector
{
    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) const final override;
};

} // namespace GeneticTSP

#endif
