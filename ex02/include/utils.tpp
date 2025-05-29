#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

#include "utils.hpp"

template <typename Container>
void printContainer(const Container& container) {
  for (typename Container::const_iterator it = container.begin();
       it != container.end(); ++it) {
    std::cout << *it;
    if (std::next(it) == container.end()) {
      std::cout << std::endl;
    } else {
      std::cout << " ";
    }
  }
}

template <typename Container>
void printContainerSub(const Container& vec, size_t left, size_t right) {
  if (left >= right || left >= vec.size() || right > vec.size()) {
    std::cout << "Invalid range [" << left << ", " << right << ")" << std::endl;
    return;
  }
  for (size_t i = left; i < right; ++i) {
    std::cout << vec[i];
    if (i + 1 < right) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

template <typename Func, typename Arg>
double measure_us(const Func& func, Arg& arg) {
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  func(arg);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> elapsed = end - start;
  return elapsed.count();
}
