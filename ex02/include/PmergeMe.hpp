#pragma once

#include <deque>
#include <iostream>
#include <vector>

#ifndef __DEBUG__
#define __DEBUG__ false
#endif

class PmergeMe {
 private:
  static void recursiveSort(std::vector<int>& data, size_t left, size_t right);
  static void recursiveSort(std::deque<int>& data, size_t left, size_t right);
  static void insertPending(std::vector<int>& sorted,
                            const std::vector<int>& pend);
  static void insertPending(std::deque<int>& sorted,
                            const std::deque<int>& pend);
  static std::vector<size_t> getJacobsthalIndices(size_t size);

  // === DEBUG ===
  static void recursiveSort_D(std::vector<int>& data, size_t left,
                              size_t right);
  static void insertPending_D(std::vector<int>& sorted,
                              const std::vector<int>& pend);

  // === OCF === (MUST not instance this class)
  PmergeMe();
  PmergeMe(const PmergeMe&);
  PmergeMe& operator=(const PmergeMe&);
  ~PmergeMe();

 public:
  static void sortVector(std::vector<int>& data);
  static void sortDeque(std::deque<int>& data);

  // === DEBUG ===
  static void sortVector_D(std::vector<int>& data);
};

template <typename Container>
void printContainer(const Container& container) {
  if (container.empty()) {
    std::cout << "Container is empty." << std::endl;
    return;
  }
  for (typename Container::const_iterator it = container.begin();
       it != container.end(); ++it) {
    if (it != container.begin()) {
      std::cout << " ";
    }
    std::cout << *it;
  }
  std::cout << std::endl;
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
