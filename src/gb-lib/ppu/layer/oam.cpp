#include "oam.h"

#include <algorithm>

#include "mem/ilocation8.h"

Oam::Oam(IMemoryView& mem)
    : mem_(mem)
{
}

auto Oam::getAll() -> std::vector<Object>
{
  std::vector<Object> result;
  result.reserve(NUM_OBJECTS);
  for (auto ptr = OAM_BASE; ptr < OAM_TOP && result.size() <= NUM_OBJECTS; ++ptr) {
    mem_.getLocation8(ptr);
  }
  return result;
}
