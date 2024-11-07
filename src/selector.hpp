#ifndef SELECTOR_HPP_INCLUDED
#define SELECTOR_HPP_INCLUDED

#include <random>
#include <vector>

namespace GeneticTSP
{

class Path;

struct Selector
{
    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) = 0;
    virtual ~Selector()                                    = default;
};

struct BestFirstSelection : Selector
{
    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) final override;
};

// https://arxiv.org/pdf/cs/0610126
struct FitnessUniformSelection : Selector
{
    FitnessUniformSelection(std::random_device::result_type seed);

    virtual std::vector<size_t>
    select_reproduce(const std::vector<Path>   &paths,
                     const std::vector<size_t> &to_delete) final override;

  private:
    using random_engine_type = std::default_random_engine;
    using distribution_type =
        std::uniform_int_distribution<random_engine_type::result_type>;
    random_engine_type rng_engine;
};

} // namespace GeneticTSP

#endif
