#include "testbank.h"

std::vector<uint8_t> TestBank::buffer_ = std::vector<uint8_t>(0x10000U, 0U);

TestBank::TestBank(const MemoryArea& area)
    : b_(area, buffer_)
    , l(*this, 0U)
{
}

auto TestBank::getLocation8(const address_type address) -> ILocation8& { return b_.getLocation8(address); }

auto TestBank::getLocation16(const address_type address) -> ILocation16&
{
  l.setAddress(address);
  return l;
}

auto TestBank::staticBank() -> IMemoryWordView&
{
  static std::vector<uint8_t> buffer = std::vector<uint8_t>(0x10000U, 0U);
  static IMemoryWordViewUP mem = std::make_unique<TestBank>(MemoryArea { 0x0000U, 0xFFFFU });
  return *mem;
}
