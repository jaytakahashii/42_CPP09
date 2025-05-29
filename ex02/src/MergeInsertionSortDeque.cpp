#include "MergeInsertionSortDeque.hpp"

#include <algorithm>
#include <iostream>

// メインの呼び出し関数
void MergeInsertionSortDeque::sort(std::deque<int>& data) {
  if (data.size() <= 1)
    return;
  recursiveSort(data, 0, data.size());
}

// データの範囲を [left, right) として再帰的にソート
void MergeInsertionSortDeque::recursiveSort(std::deque<int>& data, size_t left,
                                            size_t right) {
  size_t size = right - left;
  if (size <= 1)
    return;

  std::deque<int> bigger, pending;

  // ペアを作成
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

  // sorted に初期要素を追加
  std::deque<int> sorted;
  sorted.push_back(pending[0]);  // 先頭の pending をまず入れる
  pending.pop_front();

  // bigger の要素を追加（昇順）
  sorted.insert(sorted.end(), bigger.begin(), bigger.end());

  // pending の残りを Jacobsthal 順に挿入
  insertPending(sorted, pending);

  // 結果を data に書き戻す
  for (size_t i = 0; i < sorted.size(); ++i) {
    data[left + i] = sorted[i];
  }
}

// Jacobsthal 順＋逆順で挿入
void MergeInsertionSortDeque::insertPending(std::deque<int>& sorted,
                                            const std::deque<int>& pend) {
  size_t n = pend.size();
  std::vector<size_t> jacobIndices = getJacobsthalIndices(n);

  std::vector<bool> used(n, false);
  for (size_t i = 0; i < jacobIndices.size(); ++i) {
    if (jacobIndices[i] >= n)
      break;
    used[jacobIndices[i]] = true;
    std::deque<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), pend[jacobIndices[i]]);
    sorted.insert(pos, pend[jacobIndices[i]]);
  }

  // 未使用のインデックスを逆順に挿入
  for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
    if (!used[i]) {
      std::deque<int>::iterator pos =
          std::lower_bound(sorted.begin(), sorted.end(), pend[i]);
      sorted.insert(pos, pend[i]);
    }
  }
}

// Jacobsthal 数列のインデックスを取得
std::vector<size_t> MergeInsertionSortDeque::getJacobsthalIndices(size_t size) {
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
