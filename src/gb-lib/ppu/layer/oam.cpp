#include "oam.h"

#include <algorithm>
#include <array>

#include "location/location.h"

Oam::Oam(IMemoryViewSP mem)
    : mem_(std::move(mem))
{
}

auto Oam::getAll() -> std::array<Object, NUM_OBJECTS>
{
  std::array<Object, NUM_OBJECTS> result;
  for (auto ptr = OAM_BASE; ptr < OAM_TOP; ++ptr) {
    mem_->getByte(ptr);
  }
  return result;
}
