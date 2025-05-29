#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(uint8_t& buffer)
    : BufferLocation(buffer)
    , mbc_(nullptr)
    , address_(0x0000U)
{
}

auto RomLocation::operator=(const uint8_t& rhs) -> RomLocation&
{
  if (mbc_ != nullptr) {
    mbc_->handleWrite(address_, rhs);
  }
  return *this;
}

void RomLocation::setMbc(Mbc* value) { mbc_ = value; }

void RomLocation::setAddress(const address_type value) { address_ = value; }
