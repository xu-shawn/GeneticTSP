#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include "mutator.hpp"
#include "parse.hpp"
#include "selector.hpp"
#include "simulation.hpp"
#include "terminator.hpp"

using namespace GeneticTSP;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: GeneticTSP [filename]" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file_input;
    file_input.open(argv[1]);

    std::ofstream file_output("best_path.txt");

    Simulation simulation(graph_from_coordinates(parse_coordinates(file_input)),
                          128, 42);

    std::unique_ptr<Terminator> terminator_fpd =
        std::make_unique<FitnessProbablisticDeletion>(42);
    std::unique_ptr<Selector> selector_bfs =
        std::make_unique<BestFirstSelection>();

    std::unique_ptr<Terminator> terminator_FUSS =
        std::make_unique<FitnessUniformDeletion>();
    std::unique_ptr<Selector> selector_FUSS =
        std::make_unique<FitnessUniformSelection>(42);

    std::unique_ptr<Mutator> mutator_swap = std::make_unique<EdgeSwap>(42);
    std::unique_ptr<Mutator> mutator_range_reverse =
        std::make_unique<RangeReverse>(42);

    Path::weight_type last_weight = simulation.paths[0].total_weight();
    Path::weight_type curr_weight;

    for (int generation = 0;; generation++)
    {
        curr_weight =
            std::min_element(begin(simulation.paths), end(simulation.paths))
                ->total_weight();

        if (curr_weight != last_weight)
        {
            last_weight = curr_weight;
            std::cout << "Generation: " << generation
                      << ", Best: " << curr_weight << std::endl;

            file_output << "Generation: " << generation
                        << ", Weight: " << curr_weight << "\n"
                        << simulation.paths[0].to_string() << "\n"
                        << std::endl;
        }

        simulation.step(*terminator_fpd, *selector_bfs, *mutator_range_reverse);
    }

    return 0;
}
