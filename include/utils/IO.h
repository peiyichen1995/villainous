#pragma once

#include <iomanip>
#include <iostream>

namespace utils {
template <typename Arg, typename... Args>
void log(const std::string &header, Arg &&arg, Args &&...args);

template <typename T, typename... Args>
void userInput(T &value, Args &&...args);

namespace detail {
void logHeader(const std::string &header);
} // namespace detail
} // namespace utils

////////////////////////////////////////////////////////////////////////////////////
// Implementations
////////////////////////////////////////////////////////////////////////////////////

namespace utils {
template <typename Arg, typename... Args>
void log(const std::string &header, Arg &&arg, Args &&...args) {
  detail::logHeader(header);
  std::cout << arg;
  if (sizeof...(args) > 0)
    (std::cout << ... << args);
  std::cout << std::endl;
}

template <typename T, typename... Args>
void requestUserInput(T &value, Args &&...args) {
  log("USER INPUT", std::forward<Args>(args)...);

  detail::logHeader("USER INPUT");
  std::cin >> value;
}

template <typename... Args>
void requestUserInputLine(std::string &value, Args &&...args) {
  log("USER INPUT", std::forward<Args>(args)...);

  detail::logHeader("USER INPUT");
  std::getline(std::cin, value);
}
} // namespace utils