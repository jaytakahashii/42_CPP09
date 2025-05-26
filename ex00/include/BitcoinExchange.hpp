#pragma once

#include <map>
#include <string>

class BitcoinExchange {
 private:
  std::map<std::string, float> _exchangeRates;

 public:
  // === OCF ===
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange&);
  BitcoinExchange& operator=(const BitcoinExchange&);
  ~BitcoinExchange();

  // === Constructor ===
  BitcoinExchange(const std::string& databaseFile);
};
