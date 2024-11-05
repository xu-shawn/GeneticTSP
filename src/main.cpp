#include <fstream>
#include <iostream>
#include <random>

#include "parse.hpp"
#include "simulation.hpp"

using namespace GeneticTSP;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: GeneticTSP [filename]" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file_input;
    file_input.open(argv[0]);

    Simulation<1000> simulation(
        graph_from_coordinates(parse_coordinates(file_input)),
        std::random_device{});

    simulation.step();

    return 0;
}
