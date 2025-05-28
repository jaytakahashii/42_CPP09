#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"

static bool isValidArgument(const std::string& arg,
                            std::vector<int>& vectorNumbers,
                            std::deque<int>& dequeNumbers) {
  for (size_t i = 0; i < arg.length(); ++i) {
    if (isspace(static_cast<unsigned char>(arg[i]))) {
      continue;
    }
    char* endPtr;
    if (isdigit(static_cast<unsigned char>(arg[i]))) {
      long number = std::strtol(&arg[i], &endPtr, 10);
      if (endPtr == &arg[i] || number < 0 || number > INT_MAX) {
        return false;
      } else {
        vectorNumbers.push_back(static_cast<int>(number));
        dequeNumbers.push_back(static_cast<int>(number));
        i = endPtr - arg.c_str() - 1;
      }
    } else {
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << RED << "Error: invalid number of arguments." << RESET
              << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<int> vectorNumbers;
  std::deque<int> dequeNumbers;

  if (!isValidArgument(argv[1], vectorNumbers, dequeNumbers)) {
    std::cerr << RED << "Error: invalid argument format." << RESET << std::endl;
    return EXIT_FAILURE;
  }

  for (std::vector<int>::const_iterator it = vectorNumbers.begin();
       it != vectorNumbers.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
