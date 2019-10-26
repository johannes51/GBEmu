#include "rambank.h"

#include "location/location.h"
#include "location/rambyte.h"

RamBank::RamBank(MemoryArea area)
    : SingleAreaManager(area)
    , start_(area.from)
    , size_(area.to - area.from + 1)
    , buffer_(size_)
{
}

Location<uint8_t> RamBank::getByte(address_type address)
{
  auto index = static_cast<int>(address) - static_cast<int>(start_);
  if (index < 0 || index > size_ - 1) {
    throw std::invalid_argument("Out of bounds");
  }
  return Location<uint8_t>::generate(std::make_unique<RamByte>(buffer_.at(index)));
}

Location<uint16_t> RamBank::getWord(address_type address)
{
  auto index = address - start_;
  if (index < 0 || index > size_ - 2) {
    throw std::invalid_argument("Out of bounds");
  }
  return Location<uint16_t>::generate(
      std::make_unique<RamByte>(buffer_.at(index)), std::make_unique<RamByte>(buffer_.at(index + 1)));
}
