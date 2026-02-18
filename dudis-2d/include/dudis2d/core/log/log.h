// #include <string>

// #pragma once

// namespace dudis {

// #define D_RESET "\033[0m"
// #define D_RED "\033[31m"
// #define D_GREEN "\033[32m"
// #define D_YELLOW "\033[33m"
// #define D_BLUE "\033[34m"
// #define D_BOLD "\033[1m"

// class Log {
// public:
//   static void Error(const std::string &error);
//   static void Info(const std::string &info);
//   static void Alert(const std::string &alert);
//   static void Success(const std::string &success);
// };
// }; // namespace dudis

#pragma once
#include <iostream>
#include <string>

namespace dudis {

#define D_RESET "\033[0m"
#define D_RED "\033[31m"
#define D_GREEN "\033[32m"
#define D_YELLOW "\033[33m"
#define D_BLUE "\033[34m"
#define D_BOLD "\033[1m"

class Log {
public:
  inline static void Error(const char *error) {
#if DD_DEBUG
    std::cout << D_RED << D_BOLD << error << D_RESET << std::endl;
#endif
  }

  inline static void Alert(const char *alert) {
#if DD_DEBUG
    std::cout << D_YELLOW << alert << D_RESET << std::endl;
#endif
  }

  inline static void Info(const char *info) {
#if DD_DEBUG
    std::cout << D_BLUE << info << D_RESET << std::endl;
#endif
  }

  inline static void Success(const char *success) {
#if DD_DEBUG
    std::cout << D_GREEN << D_BOLD << success << D_RESET << std::endl;
#endif
  }
};

} // namespace dudis