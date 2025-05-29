#include "mem_tools.h"

#include <numeric>
#include <stdexcept>

auto mem_tools::translateAddressSafe(const address_type& inputAddress, const MemoryArea& area) -> address_type
{
  assertSafe(inputAddress, area);
  return inputAddress - area.from;
}

auto mem_tools::translateAddressSafe(
    const address_type& inputAddress, const address_type& startAddress, const address_type& size) -> address_type
{
  assertSafe(inputAddress, startAddress, size);
  return inputAddress - startAddress;
}

auto mem_tools::translateAddressSafe(
    const address_type& inputAddress, const MemoryArea& mirror, const int offset) -> address_type
{
  assertSafe(inputAddress, mirror);
  return inputAddress + offset;
}

void mem_tools::assertSafe(const address_type& address, const MemoryArea& area)
{
  if (!isSafe(address, area)) {
    throw std::invalid_argument("Out of bounds");
  }
}

void mem_tools::assertSafe(const address_type& inputAddress, const address_type& startAddress, const address_type& size)
{
  if (!isSafe(inputAddress, startAddress, size)) {
    throw std::invalid_argument("Out of bounds");
  }
}

auto mem_tools::isSafe(const address_type& address, const MemoryArea& area) -> bool
{
  return ((address >= area.from) && (address <= area.to));
}

auto mem_tools::isSafe(
    const address_type& inputAddress, const address_type& startAddress, const address_type& size) -> bool
{
  return (inputAddress >= startAddress && inputAddress < startAddress + size);
}

auto mem_tools::isDisjunct(const MemoryArea& area, const std::vector<MemoryArea>& oldAreas) -> bool
{
  return std::accumulate(oldAreas.cbegin(), oldAreas.cend(), true,
      [area](const auto& a, const auto& b) { return a && isDisjunct(area, b); });
}

auto mem_tools::isDisjunct(const MemoryArea& area1, const MemoryArea& area2) -> bool
{
  return (area1.to < area2.from) || (area1.from > area2.to);
}
