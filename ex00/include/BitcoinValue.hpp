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

  bool _isValidInputHeader(const std::string&) const;
  bool _parseLine(const std::string&, BitcoinData&);
  bool _isValidDate(const std::string&) const;
  bool _isValidValue(const std::string&, float&) const;

  // === Delete Methods ===
  BitcoinValue();

 public:
  // === OCF ===

  BitcoinValue(const BitcoinValue&);
  BitcoinValue& operator=(const BitcoinValue&);
  ~BitcoinValue();

  // === Constructor ===
  BitcoinValue(const std::string&, const std::string&);

  // === Methods ===

  void processAndPrint() const;
};
