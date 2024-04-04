#include "utils/IO.h"

namespace utils {
namespace detail {
void logHeader(const std::string &header) {
  std::cout << "|" << std::setw(15) << header << "| ";
}
} // namespace detail

std::string getUserInput() {
  std::string input;
  std::getline(std::cin, input);
  return input;
}
} // namespace utils