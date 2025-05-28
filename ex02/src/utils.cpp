#include "utils.hpp"

#include <iostream>
#include <string>

void printVector(const std::vector<int>& vectorNumbers) {
  for (std::vector<int>::const_iterator it = vectorNumbers.begin();
       it != vectorNumbers.end(); ++it) {
    std::cout << *it;
    if (it == vectorNumbers.end()) {
      std::cout << std::endl;
    } else {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

void printDeque(const std::deque<int>& dequeNumbers) {
  for (std::deque<int>::const_iterator it = dequeNumbers.begin();
       it != dequeNumbers.end(); ++it) {
    std::cout << *it;
    if (it == dequeNumbers.end()) {
      std::cout << std::endl;
    } else {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}
