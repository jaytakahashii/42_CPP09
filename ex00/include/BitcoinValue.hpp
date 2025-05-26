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

  bool parseLine(const std::string& line, BitcoinData& data);
  bool isValidDate(const std::string& date) const;
  bool isValidValue(const std::string& valueStr, float& value) const;

 public:
  BitcoinValue(const std::string& inputFile, const std::string& rateFile);
  ~BitcoinValue();
  void processAndPrint() const;
};
