#include "mem_tools.h"

#include <stdexcept>

#include <numeric>

auto mem_tools::translateAdressSafe(const address_type& inputAdress, const MemoryArea& area) -> address_type
{
  assertSafe(inputAdress, area);
  return inputAdress - area.from;
}

auto mem_tools::translateAdressSafe(
    const address_type& inputAdress, const address_type& startAdress, const address_type& size) -> address_type
{
  assertSafe(inputAdress, startAdress, size);
  return inputAdress - startAdress;
}

auto mem_tools::translateAdressSafe(const address_type& inputAdress, const MemoryArea& mirror, const int offset)
    -> address_type
{
  assertSafe(inputAdress, mirror);
  return inputAdress + offset;
}

void mem_tools::assertSafe(const address_type& address, const MemoryArea& area)
{
  if (!isSafe(address, area)) {
    throw std::invalid_argument("Out of bounds");
  }
}

void mem_tools::assertSafe(const address_type& inputAdress, const address_type& startAdress, const address_type& size)
{
  if (!isSafe(inputAdress, startAdress, size)) {
    throw std::invalid_argument("Out of bounds");
  }
}

auto mem_tools::isSafe(const address_type& address, const MemoryArea& area) -> bool
{
  return (address >= area.from && address <= area.to);
}

auto mem_tools::isSafe(const address_type& inputAdress, const address_type& startAdress, const address_type& size)
    -> bool
{
  return (inputAdress >= startAdress && inputAdress < startAdress + size);
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
