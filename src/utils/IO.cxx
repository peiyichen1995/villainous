#include "utils/IO.h"

namespace utils {
namespace detail {
void logHeader(const std::string &header) {
  std::cout << "|" << std::setw(15) << header << "| ";
}
} // namespace detail
} // namespace utils