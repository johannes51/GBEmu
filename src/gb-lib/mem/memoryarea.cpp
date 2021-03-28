#include "memoryarea.h"

#include <stdexcept>

auto operator<(const MemoryArea& lhs, const MemoryArea& rhs) -> bool { return lhs.from < rhs.from; }

auto operator==(const MemoryArea& lhs, const MemoryArea& rhs) -> bool
{
  return lhs.from == rhs.from && lhs.to == rhs.to;
}
