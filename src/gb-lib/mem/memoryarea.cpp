#include "memoryarea.h"

#include <stdexcept>

auto MemoryArea::size() const -> size_t { return (to - from) + 1U; }

auto operator<(const MemoryArea& lhs, const MemoryArea& rhs) -> bool { return lhs.from < rhs.from; }

auto operator==(const MemoryArea& lhs, const MemoryArea& rhs) -> bool
{
  return lhs.from == rhs.from && lhs.to == rhs.to;
}
