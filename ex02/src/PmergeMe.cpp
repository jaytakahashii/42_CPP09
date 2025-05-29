#include "PmergeMe.hpp"

#include <iostream>

#include "color.hpp"

void PmergeMe::sortVector(std::vector<int>& data) {
  if (data.size() <= 1)
    return;
  recursiveSort(data, 0, data.size());
}

void PmergeMe::sortDeque(std::deque<int>& data) {
  if (data.size() <= 1)
    return;
  recursiveSort(data, 0, data.size());
}

void PmergeMe::recursiveSort(std::vector<int>& data, size_t left,
                             size_t right) {
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

void PmergeMe::recursiveSort(std::deque<int>& data, size_t left, size_t right) {
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

void PmergeMe::insertPending(std::vector<int>& sorted,
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

void PmergeMe::insertPending(std::deque<int>& sorted,
                             const std::deque<int>& pend) {
  size_t n = pend.size();
  std::vector<size_t> jacobIndices = getJacobsthalIndices(n);
  std::vector<bool> used(n, false);

  for (size_t idx = 0; idx < jacobIndices.size(); ++idx) {
    if (jacobIndices[idx] >= n)
      break;
    used[jacobIndices[idx]] = true;
    int value = pend[jacobIndices[idx]];
    std::deque<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), value);
    sorted.insert(pos, pend[jacobIndices[idx]]);
  }

  // 未使用のインデックスを逆順に挿入
  for (int idx = static_cast<int>(n) - 1; idx >= 0; --idx) {
    if (!used[idx]) {
      int value = pend[idx];
      std::deque<int>::iterator pos =
          std::lower_bound(sorted.begin(), sorted.end(), value);
      sorted.insert(pos, value);
    }
  }
}

std::vector<size_t> PmergeMe::getJacobsthalIndices(size_t size) {
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

// === DEBUG ===

void PmergeMe::sortVector_D(std::vector<int>& data) {
  if (data.size() <= 1)
    return;
  recursiveSort_D(data, 0, data.size());
}

// 再帰的に sort
void PmergeMe::recursiveSort_D(std::vector<int>& data, size_t left,
                               size_t right) {
  size_t size = right - left;
  if (size <= 1)
    return;

  std::cout << BOLDCYAN << "\n[recursiveSort]" << RESET << std::endl;
  std::cout << "range (" << left << ", " << right << ") , " << "size = " << size
            << std::endl;
  printContainerSub(data, left, right);

  // ステップ 1: ペア分け
  std::vector<int> bigger, pending;
  for (size_t i = 0; i + 1 < size; i += 2) {
    int a = data[left + i];
    int b = data[left + i + 1];
    std::cout << " compare: (" << a << ", " << b << ") "
              << "→ ";
    if (a > b) {
      std::cout << "bigger=" << BOLDGREEN << a << RESET << ","
                << " pending=" << BOLDMAGENTA << b << "\n"
                << RESET;
      bigger.push_back(a);
      pending.push_back(b);
    } else {
      std::cout << "bigger=" << b << ", pending=" << a << "\n";
      bigger.push_back(b);
      pending.push_back(a);
    }
  }

  // 奇数個の場合
  if (size % 2 != 0) {
    std::cout << " unpaired: " << BOLDMAGENTA << data[left + size - 1]
              << " → pending" << RESET << std::endl;
    pending.push_back(data[left + size - 1]);
  }

  // ステップ 2: bigger をソート
  std::cout << BOLDGREEN << " bigger:  ";
  printContainer(bigger);
  std::cout << RESET;
  std::cout << BOLDMAGENTA << " pending: ";
  printContainer(pending);
  std::cout << RESET;
  recursiveSort_D(bigger, 0, bigger.size());

  // ステップ 3: sorted の初期化
  std::cout << BOLDWHITE << "\n [Start Insertion] " << RESET << std::endl;
  std::cout << BOLDGREEN << " now bigger:  ";
  printContainer(bigger);
  std::cout << RESET;
  std::cout << BOLDMAGENTA << " now pending: ";
  printContainer(pending);
  std::cout << RESET;
  std::vector<int> sorted;
  std::cout << " initial sorted: " << BOLDMAGENTA << "pending[" << RESET << "0"
            << BOLDMAGENTA << "] = " << pending[0] << RESET
            << " → insert at sorted[0]" << std::endl;
  sorted.push_back(pending[0]);
  pending.erase(pending.begin());

  sorted.insert(sorted.end(), bigger.begin(), bigger.end());
  std::cout << BOLDGREEN << " bigger(sorted):  ";
  printContainer(sorted);
  std::cout << RESET;

  // ステップ 4: pending を Jacobsthal 順で挿入
  insertPending_D(sorted, pending);

  // 書き戻し
  for (size_t i = 0; i < sorted.size(); ++i) {
    data[left + i] = sorted[i];
  }
  std::cout << BOLDWHITE << "\n Now Data: ";
  printContainer(data);
  std::cout << RESET;
  std::cout << BOLDWHITE << " [End Insertion] " << RESET << std::endl;
}

void PmergeMe::insertPending_D(std::vector<int>& sorted,
                               const std::vector<int>& pend) {
  std::cout << BOLDWHITE << "\n  [Insert Pending]" << RESET << std::endl;
  size_t n = pend.size();
  std::vector<size_t> jacobIndices = getJacobsthalIndices(n);
  std::vector<bool> used(n, false);

  std::cout << BOLDMAGENTA << "  pending = ";
  printContainer(pend);
  std::cout << RESET;

  std::cout << BOLDYELLOW << "  Jacobsthal order indices = ";
  printContainer(jacobIndices);
  std::cout << RESET << std::endl;

  for (size_t idx = 0; idx < jacobIndices.size(); ++idx) {
    if (idx >= n)
      break;
    used[idx] = true;
    int value = pend[idx];
    std::vector<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), value);
    std::cout << "  insert " << value << " at position "
              << (pos - sorted.begin()) << BOLDYELLOW << " (Jacobsthal)"
              << RESET << std::endl;
    sorted.insert(pos, value);
  }

  // 残りを逆順で挿入
  for (int idx = static_cast<int>(n) - 1; idx >= 0; --idx) {
    if (!used[idx]) {
      int value = pend[idx];
      std::vector<int>::iterator pos =
          std::lower_bound(sorted.begin(), sorted.end(), value);
      std::cout << "  insert " << value << " at position "
                << (pos - sorted.begin()) << " (reverse remaining)\n";
      sorted.insert(pos, value);
    }
  }
}
