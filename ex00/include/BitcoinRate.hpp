#pragma once

#include <map>
#include <string>

class BitcoinRate {
 private:
  std::map<std::string, float> _rateMap;

  BitcoinRate();

 public:
  // === OCF ===
  BitcoinRate(const BitcoinRate& other);
  BitcoinRate& operator=(const BitcoinRate& other);
  ~BitcoinRate();

  // === Constructor ===
  BitcoinRate(const std::string& filename);

  // === Methods ===
  bool hasClosestRate(const std::string& date, float& rate) const;
};
