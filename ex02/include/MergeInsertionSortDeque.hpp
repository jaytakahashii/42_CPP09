#pragma once

#include <deque>

class MergeInsertionSortDeque {
 private:
  static void recursiveSort(std::deque<int>& data, size_t left, size_t right);
  static void insertPending(std::deque<int>& sorted,
                            const std::deque<int>& pend);
  static std::vector<size_t> getJacobsthalIndices(size_t size);

  // === OCF === (MUST not instance this class)
  MergeInsertionSortDeque();
  MergeInsertionSortDeque(const MergeInsertionSortDeque&);
  MergeInsertionSortDeque& operator=(const MergeInsertionSortDeque&);
  ~MergeInsertionSortDeque();

 public:
  static void sort(std::deque<int>& data);
};
