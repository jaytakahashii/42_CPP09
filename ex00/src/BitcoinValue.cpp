#include "BitcoinValue.hpp"

#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

// === Public Static Method ===

void BitcoinValue::bitcoinExchange(const std::string& inputFile,
                                   const std::string& rateDBFile) {
  BitcoinRate rateDB = BitcoinRate(rateDBFile);

  std::ifstream file(inputFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open input file");
  }

  std::string line;
  std::getline(file, line);
  if (!_isValidInputHeader(line)) {
    throw std::runtime_error("invalid input header");
  }

  _calculateAndPrint(file, rateDB);
}

// === Private Methods ===

// ヘッダが正しいか検証
bool BitcoinValue::_isValidInputHeader(const std::string& inputHeader) {
  return (inputHeader == "date | value");
}

// データ行を読み取り、計算と出力
void BitcoinValue::_calculateAndPrint(std::ifstream& file,
                                      const BitcoinRate& rateDB) {
  std::string line;
  while (std::getline(file, line)) {
    BitcoinData data;
    if (_parseLine(line, data)) {
      float rate;
      if (rateDB.hasClosestRate(data.date, rate)) {
        double result =
            static_cast<double>(rate) * static_cast<double>(data.value);
        std::cout << data.date << " => " << data.value << " = " << result
                  << std::endl;
      } else {
        std::cout << "Error: no rate found for date => '" << data.date << "'"
                  << std::endl;
      }
    }
  }
}

bool BitcoinValue::_parseLine(const std::string& line, BitcoinData& data) {
  // パイプの位置を確認
  size_t pipePos = line.find('|');
  if (pipePos == std::string::npos || pipePos != 11 || line.length() < 13) {
    std::cout << "Error: bad input => '" << line << "'" << std::endl;
    return false;
  }

  // 日付部分と値部分を明示的に取得
  std::string datePart = line.substr(0, 10);
  std::string spaceBefore = line.substr(10, 1);  // パイプ前の空白
  std::string spaceAfter = line.substr(12, 1);   // パイプ後の空白（1文字目）
  std::string valuePart = line.substr(13);       // 値の実体

  // pipeの前後に空白があるか確認
  if (spaceBefore != " " || spaceAfter != " ") {
    std::cout << "Error: bad input => '" << line << "'" << std::endl;
    return false;
  }

  if (!_isValidDate(datePart)) {
    std::cout << "Error: bad input => '" << line << "'" << std::endl;
    return false;
  }

  float value;
  if (!_isValidValue(valuePart, value)) {
    return false;
  }

  data.date = datePart;
  data.value = value;
  return true;
}

// 日付形式チェック + うるう年対応
bool BitcoinValue::_isValidDate(const std::string& date) {
  if (date.empty() || date.length() != 10 || date[4] != '-' || date[7] != '-')
    return false;

  // 年月日の部分が数字であることを確認
  for (size_t i = 0; i < date.length(); ++i) {
    if (i == 4 || i == 7)
      continue;  // ハイフンはスキップ
    if (!std::isdigit(date[i])) {
      return false;
    }
  }

  // 年月日の部分を整数に変換
  int y = std::atoi(date.substr(0, 4).c_str());
  int m = std::atoi(date.substr(5, 2).c_str());
  int d = std::atoi(date.substr(8, 2).c_str());

  if (y < 0 || m < 1 || m > 12 || d < 1)
    return false;

  const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int maxDay = daysInMonth[m - 1];
  if (m == 2 && _isLeapYear(y))
    maxDay = 29;

  return d <= maxDay;
}

// うるう年判定
bool BitcoinValue::_isLeapYear(int year) {
  if (year % 4 != 0)
    return false;
  if (year % 100 != 0)
    return true;
  return (year % 400 == 0);
}

// 値のバリデーション
bool BitcoinValue::_isValidValue(const std::string& valueStr, float& value) {
  if (valueStr.empty()) {
    std::cout << "Error: empty value." << std::endl;
    return false;
  }

  if (!std::isdigit(valueStr[0]) && valueStr[0] != '-') {
    std::cout << "Error: not a valid number : '" << valueStr << "'"
              << std::endl;
    return false;
  }

  char* endptr;
  std::string copy = valueStr;
  value = std::strtod(copy.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cout << "Error: not a valid number : '" << valueStr << "'"
              << std::endl;
    return false;
  }

  if (value < 0) {
    std::cout << "Error: not a positive number." << std::endl;
    return false;
  }

  if (value > 1000) {
    std::cout << "Error: too large a number." << std::endl;
    return false;
  }

  return true;
}
