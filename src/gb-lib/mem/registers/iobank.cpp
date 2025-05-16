#include "iobank.h"

IoBank::IoBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : RamBank(area, buffer)
{
}

auto IoBank::getLocation8(const address_type address) -> Location8 { return RamBank::getLocation8(address); }

auto IoBank::getLocation16(const address_type address) -> Location16 { return RamBank::getLocation16(address); }

auto IoBank::getRegisterLocation(const address_type address) -> ByteLocationAdapterUP
{
  return std::make_unique<BufferLocation>(getByteReference(address));
}
