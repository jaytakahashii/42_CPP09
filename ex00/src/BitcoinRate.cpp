#include "BitcoinRate.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

BitcoinRate::BitcoinRate() {
  // Default constructor does nothing
}
BitcoinRate::BitcoinRate(const BitcoinRate& other) : _rateMap(other._rateMap) {
  // Copy constructor
}
BitcoinRate& BitcoinRate::operator=(const BitcoinRate& other) {
  if (this != &other) {
    _rateMap = other._rateMap;
  }
  return *this;
}
BitcoinRate::~BitcoinRate() {
  // Destructor does nothing, as we are not managing any dynamic memory
  // but it is needed for OCF compliance
}

BitcoinRate::BitcoinRate(const std::string& filename) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open data file");
  }

  std::string line;
  std::getline(file, line);  // skip header line

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string date;
    std::string valueStr;

    if (std::getline(iss, date, ',') && std::getline(iss, valueStr)) {
      std::istringstream vs(valueStr);
      float value;
      vs >> value;
      _rateMap[date] = value;
    }
  }
}

float BitcoinRate::getRateForDate(const std::string& date) const {
  std::map<std::string, float>::const_iterator it = _rateMap.find(date);
  if (it != _rateMap.end()) {
    return it->second;
  }
  throw std::runtime_error("no rate found for date: " + date);
}

bool BitcoinRate::hasClosestRate(const std::string& date, float& rate) const {
  std::map<std::string, float>::const_iterator it = _rateMap.lower_bound(date);
  if (it != _rateMap.end() && it->first == date) {
    rate = it->second;
    return true;
  }
  if (it != _rateMap.begin()) {
    --it;
    rate = it->second;
    return true;
  }
  return false;
}
