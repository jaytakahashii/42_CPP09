#include <iostream>

#include "BitcoinValue.hpp"
#include "color.hpp"

#define DATA_FILE "data/data.csv"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }

  try {
    BitcoinValue processor(argv[1], DATA_FILE);
    processor.processAndPrint();
  } catch (std::exception& e) {
    std::cerr << RED "Error: " << e.what() << RESET << std::endl;
    return 1;
  }

  return 0;
}
