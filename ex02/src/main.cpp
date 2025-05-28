#include <iostream>

#include "color.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << RED << "Error: invalid number of arguments." << RESET
              << std::endl;
    return EXIT_FAILURE;
  }
  std::string arg1 = argv[1];
  std::cout << "Argument received: " << arg1 << std::endl;
  return EXIT_SUCCESS;
}
