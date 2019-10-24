#include "memoryarea.h"

#include <stdexcept>

bool operator<(const MemoryArea &lhs, const MemoryArea &rhs) {
  bool result = false;
  if (lhs.to < rhs.from) {
    result = true;
  } else if (lhs.from <= rhs.to || rhs.to >= lhs.from) {
    throw std::invalid_argument("Intersecting");
  }
  return result;
}

bool operator==(const MemoryArea &lhs, const MemoryArea &rhs) {
  return lhs.from == rhs.from && lhs.to == rhs.to;
}
