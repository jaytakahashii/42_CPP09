#include <iostream>
#include <string>

#include "BitcoinExchange.hpp"
#include "color.hpp"

static bool isValidFileName(const std::string fileName) {
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << RED "Error: could not open file." RESET << std::endl;
    return EXIT_FAILURE;
  }

  std::string inputFile = argv[1];

  return 0;
}
