#ifndef TERMINATOR_HPP_INCLUDED
#define TERMINATOR_HPP_INCLUDED

#include <random>
#include <vector>

namespace GeneticTSP
{

class Simulation;

struct Terminator
{
    virtual std::vector<size_t>
    generate_eliminations(const Simulation *sim) = 0;
    virtual ~Terminator()                        = default;
};

struct FitnessProbablistic : Terminator
{
    FitnessProbablistic(std::random_device &&device);

    virtual std::vector<size_t>
    generate_eliminations(const Simulation *sim) final override;

  private:
    using random_engine_type = std::default_random_engine;
    using distribution_type =
        std::uniform_int_distribution<random_engine_type::result_type>;
    random_engine_type rng_engine;
    distribution_type  rng_distrib;
};

// https://arxiv.org/pdf/cs/0610126
struct FitnessUniform : Terminator
{
    virtual std::vector<size_t>
    generate_eliminations(const Simulation *sim) final override;
};

} // namespace GeneticTSP

#endif
