#include "terminator.hpp"

#include <random>
#include <vector>

#include "path.hpp"

namespace GeneticTSP
{

FitnessProbablistic::FitnessProbablistic(std::random_device &&device)
    : rng_engine{std::move(device())}, rng_distrib{0, 100}
{
}

std::vector<size_t>
FitnessProbablistic::generate_eliminations(const std::vector<Path> &population)
{
    std::vector<size_t> eliminated_indices;

    for (size_t i = population.size() - 1; i >= population.size() / 5; i--)
    {
        if (rng_distrib(rng_engine) < 100 * i / population.size() - 20)
        {
            eliminated_indices.push_back(i);
        }

        if (eliminated_indices.size() == population.size() / 2)
        {
            break;
        }
    }

    return eliminated_indices;
}

} // namespace GeneticTSP
