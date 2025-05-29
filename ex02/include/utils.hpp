#pragma once

#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& vectorNumbers);
void printDeque(const std::deque<int>& dequeNumbers);

template <typename Func, typename A1>
double measure_us(const Func& func, A1& a1) {
  std::chrono::high_resolution_clock::time_point start =
      std::chrono::high_resolution_clock::now();
  func(a1);
  std::chrono::high_resolution_clock::time_point end =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> elapsed = end - start;
  return elapsed.count();
}
