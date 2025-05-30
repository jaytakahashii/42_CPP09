#include "RPN.hpp"

#include <cstdlib>
#include <limits>
#include <sstream>

double RPN::evaluate(const std::string& expression) {
  std::stack<double> stack;
  std::istringstream iss(expression);
  std::string token;

  while (iss >> token) {
    if (isOperator(token)) {
      if (stack.size() < 2)
        throw std::runtime_error("Invalid expression: insufficient operands");
      double b = stack.top();
      stack.pop();
      double a = stack.top();
      stack.pop();
      double result = applyOperation(a, b, token);
      stack.push(result);
    } else {
      if (token.length() != 1 || !isdigit(token[0]))
        throw std::runtime_error("Invalid token: " + token);
      double value = std::stod(token);
      stack.push(value);
    }
  }

  if (stack.size() != 1)
    throw std::runtime_error("Invalid expression: too many operands");

  return stack.top();
}

bool RPN::isOperator(const std::string& token) {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

double RPN::applyOperation(double a, double b, const std::string& op) {
  double answer = 0.0;
  if (op == "+") {
    answer = a + b;
  } else if (op == "-") {
    answer = a - b;
  } else if (op == "*") {
    answer = a * b;
  } else if (op == "/") {
    if (b == 0.0)
      throw std::overflow_error("Division by zero");
    answer = a / b;
  } else {
    throw std::invalid_argument("Unknown operator: " + op);
  }

  if (std::isnan(answer) || std::isinf(answer)) {
    throw std::overflow_error("Result out of range");
  }

  return answer;
}
