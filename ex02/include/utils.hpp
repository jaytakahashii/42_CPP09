#pragma once

#include <chrono>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

template <typename Container>
void printContainer(const Container& container);

template <typename Func, typename Arg>
double measure_us(const Func& func, Arg& arg);

#include "utils.tpp"
