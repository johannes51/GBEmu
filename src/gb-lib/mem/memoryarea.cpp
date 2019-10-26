#include "memoryarea.h"

#include <stdexcept>

bool operator<(const MemoryArea& lhs, const MemoryArea& rhs) { return lhs.from < rhs.from; }

bool operator==(const MemoryArea& lhs, const MemoryArea& rhs) { return lhs.from == rhs.from && lhs.to == rhs.to; }
