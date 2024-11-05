#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

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

    Simulation simulation(
        graph_from_coordinates(parse_coordinates(file_input)), 128,
        std::random_device(),
        std::make_unique<FitnessProbablistic>(std::random_device()),
        std::make_unique<BestFirstSelection>());

    int last_weight = std::numeric_limits<int32_t>::max();
    int curr_weight = simulation.paths[0].total_weight();

    for (int i = 0;; i++)
    {
        curr_weight = simulation.paths[0].total_weight();

        if (curr_weight != last_weight)
        {
            last_weight = curr_weight;
            std::cout << curr_weight << std::endl;

            file_output << "Epoch: " << i << ", Weight: " << curr_weight << "\n"
                        << simulation.paths[0].to_string() << "\n"
                        << std::endl;
        }

        simulation.step();
    }

    return 0;
}
