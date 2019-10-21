#include "mem_tools.h"

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            MemoryArea area) {
  if (!isSafe(inputAdress, area)) {
    throw std::invalid_argument("Out of bounds");
  }
  return inputAdress - area.from;
}

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            const address_type startAdress,
                                            const address_type size) {
  auto result = static_cast<int>(inputAdress) - static_cast<int>(startAdress);
  if (result < 0 || result > size) {
    throw std::invalid_argument("Out of bounds");
  }
  return result;
}

address_type mem_tools::translateAdressSafe(const address_type inputAdress,
                                            MemoryArea mirror, int offset) {
  if (!isSafe(inputAdress, mirror)) {
    throw std::invalid_argument("Out of bounds");
  }
  return inputAdress + offset;
}

bool mem_tools::isSafe(const address_type &address, const MemoryArea &area) {
  return (address >= area.from && address <= area.to);
}
