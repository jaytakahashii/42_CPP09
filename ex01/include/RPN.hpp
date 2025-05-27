#pragma once

#include <stack>
#include <string>

class RPN {
 public:
  // 実行エントリポイント
  static int evaluate(const std::string& expression);

 private:
  // 入力文字列のトークン処理と評価
  static bool isOperator(const std::string& token);
  static bool applyOperation(std::stack<int>& stack, const std::string& op);

  // コピー防止
  RPN();
  RPN(const RPN&);
  RPN& operator=(const RPN&);
  ~RPN();
};
