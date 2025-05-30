#include "BitcoinExchange.hpp"

#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

#define validPipePos 11
#define validBeforeSpacePos 10
#define validAfterSpacePos 12
#define validMinLength 14
#define validValuePos 13

// === Public Static Method ===

void BitcoinExchange::bitcoinExchange(const std::string& inputFile,
                                      const std::string& rateDBFile) {
  std::map<std::string, float> rateDB;
  _loadRateDB(rateDBFile, rateDB);
  std::ifstream file(inputFile.c_str());
  if (!file.is_open()) {
    throw std::runtime_error("could not open input file");
  }

  std::string line;
  std::getline(file, line);
  if (!_isValidInputHeader(line)) {
    throw std::runtime_error("invalid input header");
  }

  _calculateAndPrint(file, rateDB);
}

// === Private Methods ===

void BitcoinExchange::_loadRateDB(const std::string& filename,
                                  std::map<std::string, float>& rateMap) {
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
      rateMap[date] = value;
    }
  }
}

bool BitcoinExchange::_hasClosestRate(
    const std::map<std::string, float>& rateDB, const std::string& date,
    float& rate) {
  std::map<std::string, float>::const_iterator it = rateDB.lower_bound(date);
  if (it != rateDB.end() && it->first == date) {
    rate = it->second;
    return true;
  }
  if (it != rateDB.begin()) {
    --it;
    rate = it->second;
    return true;
  }
  return false;
}

bool BitcoinExchange::_isValidInputHeader(const std::string& inputHeader) {
  return (inputHeader == "date | value");
}

void BitcoinExchange::_calculateAndPrint(
    std::ifstream& file, const std::map<std::string, float>& rateDB) {
  std::string line;
  while (std::getline(file, line)) {
    BitcoinData data;
    if (_parseLine(line, data)) {
      float rate;
      if (_hasClosestRate(rateDB, data.date, rate)) {
        double result =
            static_cast<double>(rate) * static_cast<double>(data.value);
        std::cout << data.date << " => " << data.value << " = " << result
                  << std::endl;
      } else {
        std::cout << "Error: no rate found for date => '" << data.date << "'"
                  << std::endl;
      }
    }
  }
}

bool BitcoinExchange::_parseLine(const std::string& line, BitcoinData& data) {
  size_t pipePos = line.find('|');
  if (pipePos == std::string::npos || pipePos != validPipePos ||
      line.length() < validMinLength) {
    std::cout << "Error: bad input => '" << line << "'" << std::endl;
    return false;
  }

  std::string datePart = line.substr(0, validBeforeSpacePos);     // date
  std::string spaceBefore = line.substr(validBeforeSpacePos, 1);  // space
  std::string spaceAfter = line.substr(validAfterSpacePos, 1);    // space
  std::string valuePart = line.substr(validValuePos);             // value

  // check spaces before and after the pipe
  if (spaceBefore != " " || spaceAfter != " ") {
    std::cout << "Error: bad input => '" << line << "'" << std::endl;
    return false;
  }

  if (!_isValidDate(datePart)) {
    std::cout << "Error: bad date format => '" << datePart << "'" << std::endl;
    return false;
  }

  float value;
  if (!_isValidValue(valuePart, value)) {
    return false;
  }

  data.date = datePart;
  data.value = value;
  return true;
}

bool BitcoinExchange::_isValidDate(const std::string& date) {
  if (date.empty() || date.length() != 10 || date[4] != '-' || date[7] != '-')
    return false;

  // check if the date part is numeric except for the hyphens
  for (size_t i = 0; i < date.length(); ++i) {
    if (i == 4 || i == 7)
      continue;  // skip hyphens
    if (!std::isdigit(date[i])) {
      return false;
    }
  }

  // convert year, month, day parts to integers
  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());

  if (year < 0 || month < 1 || month > 12 || day < 1)
    return false;

  const int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
                               31, 31, 30, 31, 30, 31};  // days in each month

  int maxDay = daysInMonth[month - 1];
  if (month == 2 && _isLeapYear(year))
    maxDay = 29;

  return day <= maxDay;
}

bool BitcoinExchange::_isLeapYear(int year) {
  if (year % 4 != 0)
    return false;
  if (year % 100 != 0)
    return true;
  return (year % 400 == 0);
}

bool BitcoinExchange::_isValidValue(const std::string& valueStr, float& value) {
  if (valueStr.empty()) {
    std::cout << "Error: empty value." << std::endl;
    return false;
  }

  if (!std::isdigit(valueStr[0]) &&
      (valueStr[0] != '-' && valueStr[0] != '+')) {
    std::cout << "Error: not a valid number : '" << valueStr << "'"
              << std::endl;
    return false;
  }

  char* endptr;
  std::string copy = valueStr;
  value = std::strtod(copy.c_str(), &endptr);
  if (*endptr != '\0') {
    std::cout << "Error: not a valid number : '" << valueStr << "'"
              << std::endl;
    return false;
  }

  if (value < 0) {
    std::cout << "Error: not a positive number." << std::endl;
    return false;
  }

  if (value > 1000) {
    std::cout << "Error: too large a number." << std::endl;
    return false;
  }

  return true;
}
