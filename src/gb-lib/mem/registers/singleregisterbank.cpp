#include "singleregisterbank.h"

#include <stdexcept>

#include "../ram/ramlocation.h"
#include "memoryregisteradapter.h"

SingleRegisterBank::SingleRegisterBank(const address_type& start, const uint8_t& initial)
    : BufferBank({ start, start }, { std::addressof(value_), 1 })
    , start_(start)
    , value_(initial)
{
}

auto SingleRegisterBank::getLocation8(const address_type address) -> Location8
{
  if (address != start_) {
    throw std::invalid_argument("Out of bounds");
  }
  return { std::make_unique<RamLocation>(this->getByteReference(start_)) };
}

auto SingleRegisterBank::getLocation16(const address_type address) -> Location16
{
  (void)address;
  throw std::invalid_argument("Out of bounds");

  return { nullptr };
}

auto SingleRegisterBank::availableAreas() -> std::vector<MemoryArea> { return { { start_, start_ } }; }

auto SingleRegisterBank::asRegister() -> IRegisterAdapterUP
{
  return std::make_unique<MemoryRegisterAdapter>(std::make_unique<RamLocation>(this->getByteReference(start_)));
}
