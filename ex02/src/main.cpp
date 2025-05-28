#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "utils.hpp"

static bool isValidArgument(const std::string& arg,
                            std::vector<int>& vectorNumbers,
                            std::deque<int>& dequeNumbers) {
  char* endPtr;
  long number = std::strtol(arg.c_str(), &endPtr, 10);
  if (*endPtr != '\0') {
    return false;
  } else {
    vectorNumbers.push_back(static_cast<int>(number));
    dequeNumbers.push_back(static_cast<int>(number));
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cerr << RED << "Error: invalid number of arguments." << RESET
              << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<int> vectorNumbers;
  std::deque<int> dequeNumbers;

  for (int i = 1; i < argc; ++i) {
    if (!isValidArgument(argv[i], vectorNumbers, dequeNumbers)) {
      std::cerr << RED << "Error: invalid argument '" << argv[i] << "'."
                << RESET << std::endl;
      return EXIT_FAILURE;
    }
  }

  std::cout << "Before:  ";
  printVector(vectorNumbers);

  std::cout << "After:   ";
  printDeque(dequeNumbers);

  return EXIT_SUCCESS;
}
