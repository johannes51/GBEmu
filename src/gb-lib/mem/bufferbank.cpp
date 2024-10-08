#include "bufferbank.h"

#include "mem_tools.h"

BufferBank::BufferBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : SingleAreaManager(area)
    , buffer_(std::move(buffer))
{
}

uint8_t& BufferBank::getByteReference(address_type address)
{
  return buffer_[mem_tools::translateAddressSafe(address, singleArea())];
}

uint16_t& BufferBank::getWordReference(address_type address)
{
  mem_tools::assertSafe(address + 1, singleArea());
  return *reinterpret_cast<uint16_t*>(&buffer_[mem_tools::translateAddressSafe(address, singleArea())]);
}
