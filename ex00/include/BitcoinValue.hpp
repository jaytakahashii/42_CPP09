#pragma once

#include <string>
#include <vector>

#include "BitcoinRate.hpp"

struct BitcoinData {
  std::string date;
  float value;
};

class BitcoinValue {
 private:
  std::vector<BitcoinData> _inputData;
  BitcoinRate _rateDB;

  // === Private Methods ===

  bool _parseLine(const std::string& line, BitcoinData& data);
  bool _isValidDate(const std::string& date) const;
  bool _isValidValue(const std::string& valueStr, float& value) const;

  // === Delete Methods ===
  BitcoinValue();

 public:
  // === OCF ===

  BitcoinValue(const BitcoinValue& other);
  BitcoinValue& operator=(const BitcoinValue& other);
  ~BitcoinValue();

  // === Constructor ===
  BitcoinValue(const std::string& inputFile, const std::string& rateFile);

  // === Methods ===

  void processAndPrint() const;
};
