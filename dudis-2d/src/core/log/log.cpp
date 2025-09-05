#include "dudis2d/core/log/log.h"
#include <iostream>

using namespace dudis;
using namespace std;

void Log::Error(const std::string &error)
{
  cout << D_RED << D_BOLD << error << D_RESET << endl;
}

void Log::Alert(const std::string &alert)
{
  cout << D_YELLOW << alert << D_RESET << endl;
}

void Log::Info(const std::string &info)
{
  cout << D_BLUE << info << D_RESET << endl;
}

void Log::Success(const std::string &success)
{
  cout << D_GREEN << D_BOLD << success << D_RESET << endl;
}