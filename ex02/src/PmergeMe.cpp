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

  // create pairs
  std::vector<std::pair<int, int> > pairs;
  std::vector<int> bigger, pending;
  for (size_t i = 0; i + 1 < size; i += 2) {
    int a = data[left + i];
    int b = data[left + i + 1];
    if (a > b) {
      bigger.push_back(a);
      pending.push_back(b);
      pairs.push_back(std::make_pair(a, b));
    } else {
      bigger.push_back(b);
      pending.push_back(a);
      pairs.push_back(std::make_pair(b, a));
    }
  }

  // odd number of elements
  if (size % 2 != 0) {
    pending.push_back(data[left + size - 1]);
  }

  // sort bigger recursively
  recursiveSort(bigger, 0, bigger.size());

  std::vector<int> sorted;

  // insert the smaller one of the first pair into sorted
  int anchorPair = 0;
  for (size_t i = 0; i < pairs.size(); ++i) {
    if (pairs[i].first == bigger[0]) {
      anchorPair = pairs[i].second;  // pair of bigger[0]
      break;
    }
  }
  sorted.push_back(anchorPair);

  // remove the pair of bigger[0] from pending
  std::vector<int>::iterator it =
      std::find(pending.begin(), pending.end(), sorted[0]);
  if (it != pending.end()) {
    pending.erase(it);
  }

  // add the bigger's element to sorted
  sorted.insert(sorted.end(), bigger.begin(), bigger.end());

  // insert the remaining pending elements in Jacobsthal order
  insertPending(sorted, pending);

  // write back to data
  for (size_t i = 0; i < sorted.size(); ++i) {
    data[left + i] = sorted[i];
  }
}

void PmergeMe::recursiveSort(std::deque<int>& data, size_t left, size_t right) {
  size_t size = right - left;
  if (size <= 1)
    return;

  std::deque<std::pair<int, int> > pairs;
  std::deque<int> bigger, pending;
  for (size_t i = 0; i + 1 < size; i += 2) {
    int a = data[left + i];
    int b = data[left + i + 1];
    if (a > b) {
      bigger.push_back(a);
      pending.push_back(b);
      pairs.push_back(std::make_pair(a, b));
    } else {
      bigger.push_back(b);
      pending.push_back(a);
      pairs.push_back(std::make_pair(b, a));
    }
  }

  if (size % 2 != 0) {
    pending.push_back(data[left + size - 1]);
  }

  recursiveSort(bigger, 0, bigger.size());

  std::deque<int> sorted;

  int anchorPair = 0;
  for (size_t i = 0; i < pairs.size(); ++i) {
    if (pairs[i].first == bigger[0]) {
      anchorPair = pairs[i].second;  // bigger[0]のペア
      break;
    }
  }
  sorted.push_back(anchorPair);

  std::deque<int>::iterator it =
      std::find(pending.begin(), pending.end(), sorted[0]);
  if (it != pending.end()) {
    pending.erase(it);
  }

  sorted.insert(sorted.end(), bigger.begin(), bigger.end());

  insertPending(sorted, pending);

  for (size_t i = 0; i < sorted.size(); ++i) {
    data[left + i] = sorted[i];
  }
}

void PmergeMe::insertPending(std::vector<int>& sorted,
                             const std::vector<int>& pend) {
  size_t n = pend.size();
  std::vector<size_t> jacobIndices = getJacobsthalIndices(n);

  std::vector<bool> used(n, false);
  for (size_t idx = 0; idx < jacobIndices.size(); ++idx) {
    if (idx >= n)
      break;
    used[idx] = true;
    std::vector<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), pend[idx]);
    sorted.insert(pos, pend[idx]);
  }

  // insert remaining elements in reverse order
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

void PmergeMe::recursiveSort_D(std::vector<int>& data, size_t left,
                               size_t right) {
  size_t size = right - left;
  if (size <= 1)
    return;

  std::cout << BOLDCYAN << "\n[recursiveSort]" << RESET << std::endl;
  std::cout << "range (" << left << ", " << right << ") , " << "size = " << size
            << std::endl;
  printContainerSub(data, left, right);

  // Step 1: create pairs
  std::vector<std::pair<int, int> > pairs;
  std::vector<int> bigger, pending;
  for (size_t i = 0; i + 1 < size; i += 2) {
    int a = data[left + i];
    int b = data[left + i + 1];
    std::cout << " compare: (" << a << ", " << b << ") "
              << "→ ";
    if (a > b) {
      std::cout << "bigger=" << BOLDGREEN << a << RESET << ","
                << " pending=" << BOLDMAGENTA << b << RESET << std::endl;
      bigger.push_back(a);
      pending.push_back(b);
      pairs.push_back(std::make_pair(a, b));
    } else {
      std::cout << "bigger=" << BOLDGREEN << b << RESET << ","
                << " pending=" << BOLDMAGENTA << a << RESET << std::endl;
      bigger.push_back(b);
      pending.push_back(a);
      pairs.push_back(std::make_pair(b, a));
    }
  }

  // odd number of elements
  if (size % 2 != 0) {
    std::cout << " unpaired: " << BOLDMAGENTA << data[left + size - 1]
              << " → pending" << RESET << std::endl;
    pending.push_back(data[left + size - 1]);
  }

  // Step 2: sort bigger recursively
  std::cout << BOLDGREEN << " bigger:  ";
  printContainer(bigger);
  std::cout << RESET;
  std::cout << BOLDMAGENTA << " pending: ";
  printContainer(pending);
  std::cout << RESET;
  recursiveSort_D(bigger, 0, bigger.size());

  // Step 3: insert the first pair's smaller element into sorted
  std::cout << BOLDWHITE << "\n [Start Insertion] " << RESET << std::endl;
  std::cout << BOLDGREEN << " now bigger:  ";
  printContainer(bigger);
  std::cout << RESET;
  std::cout << BOLDMAGENTA << " now pending: ";
  printContainer(pending);
  std::cout << RESET;
  std::vector<int> sorted;

  int anchorPair = 0;
  for (size_t i = 0; i < pairs.size(); ++i) {
    if (pairs[i].first == bigger[0]) {
      anchorPair = pairs[i].second;  // bigger[0]のペア
      break;
    }
  }

  std::cout << " initial sorted: " << BOLDMAGENTA << "pairs bigger[0]("
            << bigger[0] << "): " << anchorPair << RESET
            << " → insert at sorted[0]" << std::endl;
  sorted.push_back(anchorPair);

  std::vector<int>::iterator it =
      std::find(pending.begin(), pending.end(), anchorPair);
  if (it != pending.end()) {
    pending.erase(it);
  }

  sorted.insert(sorted.end(), bigger.begin(), bigger.end());
  std::cout << BOLDGREEN << " bigger(sorted): ";
  printContainer(sorted);
  std::cout << RESET;
  std::cout << BOLDMAGENTA << " pending:        ";
  printContainer(pending);
  std::cout << RESET;

  // Step 4: insert the remaining pending elements in Jacobsthal order
  insertPending_D(sorted, pending);

  // write back to data
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
    if (jacobIndices[idx] >= n)
      break;
    used[jacobIndices[idx]] = true;
    int value = pend[jacobIndices[idx]];
    std::vector<int>::iterator pos =
        std::lower_bound(sorted.begin(), sorted.end(), value);
    std::cout << "  insert " << value << " at position "
              << (pos - sorted.begin()) << BOLDYELLOW << " (Jacobsthal)"
              << RESET << std::endl;
    sorted.insert(pos, value);
  }

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
