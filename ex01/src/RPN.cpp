#include "RPN.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

int RPN::evaluate(const std::string& expression) {
  std::istringstream iss(expression);
  std::string token;
  std::stack<int> stack;

  while (iss >> token) {
    if (token.size() == 1 && isdigit(token[0])) {
      stack.push(token[0] - '0');
    } else if (isOperator(token)) {
      if (!applyOperation(stack, token)) {
        std::cerr << "Error" << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Error" << std::endl;
      return 1;
    }
  }

  if (stack.size() != 1) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  std::cout << stack.top() << std::endl;
  return 0;
}

bool RPN::isOperator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::applyOperation(std::stack<int>& stack, const std::string& op) {
  if (stack.size() < 2)
    return false;

  int b = stack.top();
  stack.pop();
  int a = stack.top();
  stack.pop();

  if (op == "+") {
    stack.push(a + b);
  } else if (op == "-") {
    stack.push(a - b);
  } else if (op == "*") {
    stack.push(a * b);
  } else if (op == "/") {
    if (b == 0)
      return false;
    stack.push(a / b);
  }
  return true;
}
