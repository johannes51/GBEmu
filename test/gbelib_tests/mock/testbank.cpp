#include "testbank.h"

std::vector<uint8_t> TestBank::buffer_ = std::vector<uint8_t>(0x10000U, 0U);

TestBank::TestBank(const MemoryArea& area)
    : RamBank(area, buffer_)
{
}

auto TestBank::staticBank() -> IMemoryView&
{
  static std::vector<uint8_t> buffer = std::vector<uint8_t>(0x10000U, 0U);
  static IMemoryViewUP mem = std::make_unique<TestBank>(MemoryArea { 0x0000U, 0xFFFFU });
  return *mem;
}
