#include <string>

#pragma once

namespace dudis {

#define D_RESET "\033[0m"
#define D_RED "\033[31m"
#define D_GREEN "\033[32m"
#define D_YELLOW "\033[33m"
#define D_BLUE "\033[34m"
#define D_BOLD "\033[1m"

class Log {
public:
  static void Error(const std::string &error);
  static void Info(const std::string &info);
  static void Alert(const std::string &alert);
  static void Success(const std::string &success);
};
}; // namespace dudis