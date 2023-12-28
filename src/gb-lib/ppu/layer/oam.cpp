#include "oam.h"

#include <algorithm>

#include "location/location.h"

Oam::Oam(IMemoryViewSP mem)
    : mem_(std::move(mem))
{
}

auto Oam::getAll() -> std::vector<Object>
{
  std::vector<Object> result;
  result.reserve(NUM_OBJECTS);
  for (auto ptr = OAM_BASE; ptr < OAM_TOP && result.size() <= NUM_OBJECTS; ++ptr) {
    mem_->getByte(ptr);
  }
  return result;
}
