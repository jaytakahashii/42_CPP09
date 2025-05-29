#include <deque>
#include <iostream>
#include <vector>

#include "PmergeMe.hpp"
#include "color.hpp"

template <typename Func, typename Arg>
static double measure_us(const Func& func, Arg& arg) {
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  func(arg);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> elapsed = end - start;
  return elapsed.count();
}

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
  if (__DEBUG__) {
    std::cout << BOLDWHITE "Debug mode is ON.\n" RESET << std::endl;
  }

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
  printContainer(vectorNumbers);

  double sortTimeVector;
  double sortTimeDeque;
  if (__DEBUG__) {
    sortTimeVector = measure_us(PmergeMe::sortVector_D, vectorNumbers);
    sortTimeDeque = measure_us(PmergeMe::sortDeque, dequeNumbers);
  } else {
    sortTimeVector = measure_us(PmergeMe::sortVector, vectorNumbers);
    sortTimeDeque = measure_us(PmergeMe::sortDeque, dequeNumbers);
  }

  std::cout << "AfterV:   ";
  printContainer(vectorNumbers);

  std::cout << "Time to process a range of 5 elements with std::vector:  "
            << sortTimeVector << " us" << std::endl;

  std::cout << "Time to process a range of 5 elements with std::deque:   "
            << sortTimeDeque << " us" << std::endl;

  return EXIT_SUCCESS;
}
