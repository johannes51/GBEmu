#include "bufferbank.h"

#include "mem_tools.h"

BufferBank::BufferBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : SingleAreaManager(area)
    , buffer_(buffer)
{
  if (buffer_.size() < area.size()) {
    throw std::invalid_argument("Buffer must be larger or equal in size as memory area.");
  }
}

auto BufferBank::getByteReference(address_type address) -> uint8_t&
{
  return buffer_[mem_tools::translateAddressSafe(address, singleArea())];
}
