#include "mem_tools.h"

#include <set>

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            MemoryArea area) {
  assertSafe(inputAdress, area);
  return inputAdress - area.from;
}

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            const address_type startAdress,
                                            const address_type size) {
  assertSafe(inputAdress, startAdress, size);
  return inputAdress - startAdress;
}

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            MemoryArea mirror, int offset) {
  assertSafe(inputAdress, mirror);
  return inputAdress + offset;
}

void mem_tools::assertSafe(const address_type &address,
                           const MemoryArea &area) {
  if (!isSafe(address, area)) {
    throw std::invalid_argument("Out of bounds");
  }
}

void mem_tools::assertSafe(const address_type &inputAdress,
                           const address_type &startAdress,
                           const address_type &size) {
  if (!isSafe(inputAdress, startAdress, size)) {
    throw std::invalid_argument("Out of bounds");
  }
}

bool mem_tools::isSafe(const address_type &address, const MemoryArea &area) {
  return (address >= area.from && address <= area.to);
}

bool mem_tools::isSafe(const address_type &inputAdress,
                       const address_type &startAdress,
                       const address_type &size) {
  return (inputAdress >= startAdress && inputAdress < startAdress + size);
}

bool mem_tools::isDisjunct(const MemoryArea &area,
                           const std::vector<MemoryArea> &oldAreas) {
  try {
    std::set<MemoryArea> s(oldAreas.begin(), oldAreas.end());
    s.insert(area);
  } catch (...) {
    return false;
  }
  return true;
}
