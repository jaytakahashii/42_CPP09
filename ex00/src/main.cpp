#include <iostream>

#include "BitcoinExchange.hpp"
#include "color.hpp"

#define DATA_FILE "data/data.csv"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << RED "Error: could not open file." RESET << std::endl;
    return EXIT_FAILURE;
  }

  try {
    std::string inputFile = argv[1];
    BitcoinExchange::bitcoinExchange(inputFile, DATA_FILE);
  } catch (const std::runtime_error& e) {
    std::cerr << RED "Error: " << e.what() << RESET << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}
