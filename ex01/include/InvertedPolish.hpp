#pragma once

#include <stack>
#include <string>

class InvertedPolish {
 public:
  // 実行エントリポイント
  static int evaluate(const std::string& expression);

 private:
  // 入力文字列のトークン処理と評価
  static bool isOperator(const std::string& token);
  static bool applyOperation(std::stack<int>& stack, const std::string& op);

  // コピー防止
  InvertedPolish();
  InvertedPolish(const InvertedPolish&);
  InvertedPolish& operator=(const InvertedPolish&);
  ~InvertedPolish();
};
