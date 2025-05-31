#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#include "PmergeMe.hpp"
#include "color.hpp"

template <typename Func, typename Arg>
static double measure_us(const Func& func, Arg& arg) {
  clock_t start = clock();
  func(arg);
  clock_t end = clock();
  return static_cast<double>(end - start) * 1e6 / CLOCKS_PER_SEC;
}

static bool isValidArgument(const std::string& arg,
                            std::vector<int>& vectorNumbers,
                            std::deque<int>& dequeNumbers) {
  char* endPtr;
  long number = std::strtol(arg.c_str(), &endPtr, 10);
  if (*endPtr != '\0' || endPtr == arg.c_str() || number < 0 ||
      number > std::numeric_limits<int>::max()) {
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
    std::vector<int> vectorNumbersCopy = vectorNumbers;
    PmergeMe::sortVector_D(vectorNumbersCopy);
    sortTimeVector = measure_us(PmergeMe::sortVector, vectorNumbers);
    sortTimeDeque = measure_us(PmergeMe::sortDeque, dequeNumbers);
  } else {
    sortTimeVector = measure_us(PmergeMe::sortVector, vectorNumbers);
    sortTimeDeque = measure_us(PmergeMe::sortDeque, dequeNumbers);
  }

  std::cout << "After:   ";
  printContainer(vectorNumbers);

  std::cout << "Time to process a range of 5 elements with std::vector:  "
            << sortTimeVector << " us" << std::endl;

  std::cout << "Time to process a range of 5 elements with std::deque:   "
            << sortTimeDeque << " us" << std::endl;

  if (__DEBUG__) {
    std::vector<int> vectorNumbersCopy = vectorNumbers;
    std::deque<int> dequeNumbersCopy = dequeNumbers;
    sort(vectorNumbersCopy.begin(), vectorNumbersCopy.end());
    sort(dequeNumbersCopy.begin(), dequeNumbersCopy.end());
    if (vectorNumbers == vectorNumbersCopy) {
      std::cout << BOLDGREEN "Vector is sorted correctly." RESET << std::endl;
    } else {
      std::cout << RED "Vector is NOT sorted correctly." RESET << std::endl;
    }
    if (dequeNumbers == dequeNumbersCopy) {
      std::cout << BOLDGREEN "Deque is sorted correctly." RESET << std::endl;
    } else {
      std::cout << RED "Deque is NOT sorted correctly." RESET << std::endl;
    }
  }

  return EXIT_SUCCESS;
}
