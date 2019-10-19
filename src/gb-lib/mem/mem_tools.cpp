#include "mem_tools.h"


address_type mem_tools::translateAdressSafe(address_type inputAdress, MemoryArea area)
{
  auto result = inputAdress - area.from;
  if (result < 0 || inputAdress > area.to) {
    throw std::invalid_argument("Out of bounds");
  }
  return result;
}

address_type mem_tools::translateAdressSafe(address_type inputAdress, address_type startAdress, address_type size)
{
  auto result = static_cast<int>(inputAdress) - static_cast<int>(startAdress);
  if (result < 0 || result > size) {
    throw std::invalid_argument("Out of bounds");
  }
  return result;
}

address_type mem_tools::translateAdressSafe(address_type inputAdress, MemoryArea mirror, int offset)
{
  if (inputAdress < mirror.from || inputAdress > mirror.to) {
    throw std::invalid_argument("Out of bounds");
  }
  return inputAdress + offset;
}

