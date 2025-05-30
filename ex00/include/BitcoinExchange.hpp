#pragma once

#include <map>
#include <string>

struct BitcoinData {
  std::string date;
  float value;
};

class BitcoinExchange {
 private:
  // === Private Methods ===

  static void _loadRateDB(const std::string&, std::map<std::string, float>&);
  static bool _hasClosestRate(const std::map<std::string, float>&,
                              const std::string&, float&);
  static bool _isValidInputHeader(const std::string&);
  static void _calculateAndPrint(std::ifstream&,
                                 const std::map<std::string, float>&);
  static bool _parseLine(const std::string&, BitcoinData&);
  static bool _isValidDate(const std::string&);
  static bool _isValidValue(const std::string&, float&);
  static bool _isLeapYear(int);

  // === OCF (Delete) ===

  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange&);
  BitcoinExchange& operator=(const BitcoinExchange&);
  ~BitcoinExchange();

 public:
  static void bitcoinExchange(const std::string& inputFile,
                              const std::string& rateFile);
};
