#include <iostream>

#include "BitcoinValue.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }

  try {
    BitcoinValue processor(argv[1], "../data/data.csv");
    processor.processAndPrint();
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
