#include "MergeInsertionSortVector.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

// メインの呼び出し関数
void MergeInsertionSortVector::sort(std::vector<int>& data) {
  if (data.size() <= 1)
    return;
  recursiveSort(data, 0, data.size());
}

// データの範囲を [left, right) として再帰的にソート
void MergeInsertionSortVector::recursiveSort(std::vector<int>& data,
                                             size_t left, size_t right) {
  size_t size = right - left;
  if (size <= 1)
    return;

  // ペアを作成
  std::vector<int> bigger, pending;
  for (size_t i = 0; i + 1 < size; i += 2) {
    int a = data[left + i];
    int b = data[left + i + 1];
    if (a > b) {
      bigger.push_back(a);
      pending.push_back(b);
    } else {
      bigger.push_back(b);
      pending.push_back(a);
    }
  }

  // 奇数個の場合は最後の1要素を pending に
  if (size % 2 != 0) {
    pending.push_back(data[left + size - 1]);
  }

  // bigger を再帰的にソート
  recursiveSort(bigger, 0, bigger.size());

  // sorted に小さい方（ペアの）1つを先頭に追加（Wikipedia 方式）
  std::vector<int> sorted;
  sorted.push_back(pending[0]);  // 一番最初のペアの小さい方
  pending.erase(pending.begin());

  // bigger の先頭を sorted に追加（大きい順で既に昇順）
  sorted.insert(sorted.end(), bigger.begin(), bigger.end());

  // pending の残りを Jacobsthal 数列順で挿入
  insertPending(sorted, pending);

  // data に結果を書き戻す
  for (size_t i = 0; i < sorted.size(); ++i) {
    data[left + i] = sorted[i];
  }
}

// Jacobsthal 順と逆順で binary insert
void MergeInsertionSortVector::insertPending(std::vector<int>& sorted,
                                             const std::vector<int>& pend) {
  size_t n = pend.size();
  std::vector<size_t> jacobIndices = getJacobsthalIndices(n);

  std::vector<bool> used(n, false);
  for (size_t i = 0; i < jacobIndices.size(); ++i) {
    if (i >= n)
      break;
    used[i] = true;
    std::vector<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
    sorted.insert(pos, pend[i]);
  }

  // 未使用のインデックスを逆順に処理
  for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
    if (!used[i]) {
      std::vector<int>::iterator pos =
          std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
      sorted.insert(pos, pend[i]);
    }
  }
}

// Jacobsthal 数列 J(2) 〜 n を index として取得
std::vector<size_t> MergeInsertionSortVector::getJacobsthalIndices(
    size_t size) {
  std::vector<size_t> indices;
  size_t j0 = 0, j1 = 1, jn = 0;
  while (true) {
    jn = j1 + 2 * j0;
    if (jn >= size)
      break;
    indices.push_back(jn);
    j0 = j1;
    j1 = jn;
  }
  return indices;
}
