#include "bufferbank.h"

#include "mem_tools.h"

BufferBank::BufferBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : SingleAreaManager(area)
    , buffer_(buffer)
{
}

auto BufferBank::getByteReference(address_type address) -> uint8_t&
{
  return buffer_[mem_tools::translateAddressSafe(address, singleArea())];
}

auto BufferBank::getWordReference(address_type address) -> uint16_t&
{
  mem_tools::assertSafe(address + 1, singleArea());
  return *reinterpret_cast<uint16_t*>(&buffer_[mem_tools::translateAddressSafe(address, singleArea())]);
}
