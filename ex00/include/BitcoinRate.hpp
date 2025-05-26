#pragma once

#include <map>
#include <string>

class BitcoinRate {
 private:
  std::map<std::string, float> _exchangeRates;

 public:
  // === OCF ===
  BitcoinRate();
  BitcoinRate(const BitcoinRate&);
  BitcoinRate& operator=(const BitcoinRate&);
  ~BitcoinRate();

  // === Constructor ===
  BitcoinRate(const std::string& databaseFile);
};
