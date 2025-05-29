#pragma once

#include <deque>
#include <vector>

class MergeInsertionSortDeque {
 public:
  static void sort(std::deque<int>& data);

 private:
  static void recursiveSort(std::deque<int>& data, size_t left, size_t right);
  static void insertPending(std::deque<int>& sorted,
                            const std::deque<int>& pend);
  static std::vector<size_t> getJacobsthalIndices(size_t size);
};
