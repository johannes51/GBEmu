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
