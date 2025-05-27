#include <iostream>

#include "RPN.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  return RPN::evaluate(argv[1]);
}
