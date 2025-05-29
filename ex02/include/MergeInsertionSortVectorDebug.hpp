#pragma once

#include <deque>
#include <vector>

class MergeInsertionSortVectorDebug {
 private:
  static void recursiveSort(std::vector<int>& data, size_t left, size_t right);
  static void insertPending(std::vector<int>& sorted,
                            const std::vector<int>& pend);
  static std::vector<size_t> getJacobsthalIndices(size_t size);

  // === OCF === (MUST not instance this class)
  MergeInsertionSortVectorDebug();
  MergeInsertionSortVectorDebug(const MergeInsertionSortVectorDebug&);
  MergeInsertionSortVectorDebug& operator=(
      const MergeInsertionSortVectorDebug&);
  ~MergeInsertionSortVectorDebug();

 public:
  static void sort(std::vector<int>& data);
};
