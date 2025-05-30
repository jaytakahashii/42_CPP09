#include <iostream>

#include "RPN.hpp"
#include "color.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << RED << "Error: invalid number of arguments." << RED
              << std::endl;
    return EXIT_FAILURE;
  }

  try {
    double result = RPN::evaluate(argv[1]);
    std::cout << result << std::endl;
  } catch (const std::exception& e) {
    std::cerr << RED << "Error: " << e.what() << RED << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
