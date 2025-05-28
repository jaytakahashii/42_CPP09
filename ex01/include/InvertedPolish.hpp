#pragma once

#include <stack>
#include <stdexcept>
#include <string>

class InvertedPolish {
 public:
  static double evaluate(const std::string& expression);

 private:
  static bool isOperator(const std::string& token);
  static double applyOperation(double a, double b, const std::string& op);

  // === OCF ===
  InvertedPolish();
  InvertedPolish(const InvertedPolish&);
  InvertedPolish& operator=(const InvertedPolish&);
  InvertedPolish(InvertedPolish&);
};
