#include "testbank.h"

std::vector<uint8_t> TestBank::buffer_ = std::vector<uint8_t>(1024U, 0U);

TestBank::TestBank(const MemoryArea& area)
  : RamBank(area, buffer_)
{
}
