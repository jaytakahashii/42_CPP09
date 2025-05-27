#pragma once

#include <string>

#include "BitcoinRate.hpp"

struct BitcoinData {
  std::string date;
  float value;
};

class BitcoinValue {
 private:
  // === Private Methods ===

  static bool _isValidInputHeader(const std::string&);
  static void _calculateAndPrint(std::ifstream&, const BitcoinRate&);
  static bool _parseLine(const std::string&, BitcoinData&);
  static bool _isValidDate(const std::string&);
  static bool _isValidValue(const std::string&, float&);
  static bool _isLeapYear(int);

  // === OCF (Delete) ===

  BitcoinValue();
  BitcoinValue(const BitcoinValue&);
  BitcoinValue& operator=(const BitcoinValue&);
  ~BitcoinValue();

 public:
  static void bitcoinExchange(const std::string& inputFile,
                              const std::string& rateFile);
};
