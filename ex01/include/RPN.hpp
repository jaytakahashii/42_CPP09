#pragma once

#include <stack>
#include <stdexcept>
#include <string>

class RPN {
 public:
  static double evaluate(const std::string& expression);

 private:
  static bool isOperator(const std::string& token);
  static double applyOperation(double a, double b, const std::string& op);

  // === OCF ===
  RPN();
  RPN(const RPN&);
  RPN& operator=(const RPN&);
  RPN(RPN&);
};
