#ifndef MEM_DEFINES_H
#define MEM_DEFINES_H

#include <memory>

#include "defines.h"

using address_type = uint16_t;

class IMemoryView;
using IMemoryViewSP = std::shared_ptr<IMemoryView>;

class IMemoryManager;
using IMemoryManagerSP = std::shared_ptr<IMemoryManager>;

struct MemoryArea {
  address_type from;
  address_type to;
  bool operator<(const MemoryArea &rhs) const {
    if (from > rhs.to) {
      return false;
    } else if (to < rhs.from) {
      return true;
    } else {
      throw std::invalid_argument("Intersecting");
    }
  }
};

#endif // MEM_DEFINES_H
