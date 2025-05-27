#include "BitcoinValue.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

// === Method ===

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

  calculateAndPrint(file, rateDB);
}

// === Private Method ===

bool BitcoinValue::_isValidInputHeader(const std::string& inputHeader) {
  const std::string validHeader = "date | value";
  return (inputHeader == validHeader);
}

void BitcoinValue::calculateAndPrint(std::ifstream& file,
                                     const BitcoinRate& rateDB) {
  std::string line;
  while (std::getline(file, line)) {
    BitcoinData data;
    if (_parseLine(line, data)) {
      float rate;
      if (rateDB.hasClosestRate(data.date, rate)) {
        float result = rate * data.value;
        std::cout << data.date << " => " << data.value << " = " << result
                  << std::endl;
      } else {
        std::cerr << "Error: no valid rate for date " << data.date << std::endl;
      }
    }
  }
}

bool BitcoinValue::_parseLine(const std::string& line, BitcoinData& data) {
  std::istringstream iss(line);
  std::string datePart, valuePart;

  if (!std::getline(iss, datePart, '|')) {
    std::cerr << "Error: bad input => " << line << std::endl;
    return false;
  }

  if (!std::getline(iss, valuePart)) {
    std::cerr << "Error: bad input => " << line << std::endl;
    return false;
  }

  // Trim whitespace
  datePart.erase(0, datePart.find_first_not_of(" \t"));
  datePart.erase(datePart.find_last_not_of(" \t") + 1);
  valuePart.erase(0, valuePart.find_first_not_of(" \t"));
  valuePart.erase(valuePart.find_last_not_of(" \t") + 1);

  float value;
  if (!_isValidDate(datePart)) {
    std::cerr << "Error: bad input => " << line << std::endl;
    return false;
  }

  if (!_isValidValue(valuePart, value)) {
    return false;
  }

  data.date = datePart;
  data.value = value;
  return true;
}

bool BitcoinValue::_isValidDate(const std::string& date) {
  if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    return false;

  int y, m, d;
  try {
    y = std::atoi(date.substr(0, 4).c_str());
    m = std::atoi(date.substr(5, 2).c_str());
    d = std::atoi(date.substr(8, 2).c_str());
  } catch (...) {
    return false;
  }

  if (m < 1 || m > 12 || d < 1 || d > 31)
    return false;

  // 簡易チェック（うるう年や日数は厳密にはしていません）
  return true;
}

bool BitcoinValue::_isValidValue(const std::string& valueStr, float& value) {
  std::istringstream iss(valueStr);
  if (!(iss >> value)) {
    std::cerr << "Error: bad input => " << valueStr << std::endl;
    return false;
  }

  if (value < 0) {
    std::cerr << "Error: not a positive number." << std::endl;
    return false;
  }

  if (value > 1000) {
    std::cerr << "Error: too large a number." << std::endl;
    return false;
  }

  return true;
}
