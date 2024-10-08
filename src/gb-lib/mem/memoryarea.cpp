#include "memoryarea.h"

#include <stdexcept>

size_t MemoryArea::size() const { return (to - from) + 1U; }

auto operator<(const MemoryArea& lhs, const MemoryArea& rhs) -> bool { return lhs.from < rhs.from; }

auto operator==(const MemoryArea& lhs, const MemoryArea& rhs) -> bool
{
  return lhs.from == rhs.from && lhs.to == rhs.to;
}
