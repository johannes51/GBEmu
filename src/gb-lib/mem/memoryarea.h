#ifndef MEMORYAREA_H
#define MEMORYAREA_H

#include "mem_defines.h"

struct MemoryArea {
  constexpr size_t size() const { return (to - from) + 1U; }

  address_type from;
  address_type to;
};

bool operator<(const MemoryArea& lhs, const MemoryArea& rhs);
bool operator==(const MemoryArea& lhs, const MemoryArea& rhs);

#endif // MEMORYAREA_H
