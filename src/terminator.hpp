#ifndef TERMINATOR_HPP_INCLUDED
#define TERMINATOR_HPP_INCLUDED

#include <random>
#include <vector>

namespace GeneticTSP
{

class Simulation;
class Path;

struct Terminator
{
    virtual std::vector<size_t>
    generate_eliminations(const std::vector<Path> &population) = 0;
    virtual ~Terminator() noexcept                             = default;
};

struct FitnessProbablisticDeletion : Terminator
{
    FitnessProbablisticDeletion(std::random_device::result_type seed);

    virtual std::vector<size_t>
    generate_eliminations(const std::vector<Path> &population) final override;

  private:
    using random_engine_type = std::default_random_engine;
    using distribution_type =
        std::uniform_int_distribution<random_engine_type::result_type>;
    random_engine_type rng_engine;
    distribution_type  rng_distrib;
};

// https://arxiv.org/pdf/cs/0610126
struct FitnessUniformDeletion : Terminator
{
    virtual std::vector<size_t>
    generate_eliminations(const std::vector<Path> &population) final override;
};

} // namespace GeneticTSP

#endif
