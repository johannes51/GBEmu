#include "bytewriterlocation16.h"

#include "constants.h"

ByteWriterLocation16::ByteWriterLocation16(IMemoryView& byteView, address_type address)
    : byteView_(byteView)
    , address_(address)
    , buffer_(0U)
{
}

auto ByteWriterLocation16::get() const -> const uint16_t&
{
  const auto lower = byteView_.getLocation8(address_).get();
  const auto upper = byteView_.getLocation8(address_ + 1U).get();
  buffer_ = static_cast<uint16_t>(upper << BYTE_SHIFT) | lower;
  return buffer_;
}

auto ByteWriterLocation16::operator=(const uint16_t& rhs) -> ByteWriterLocation16&
{
  const uint16_t lower = rhs & LOWER_BYTE_MASK;
  const uint16_t upper = rhs >> BYTE_SHIFT;
  byteView_.getLocation8(address_) = lower;
  byteView_.getLocation8(address_ + 1U) = upper;
  return *this;
}

void ByteWriterLocation16::setAddress(address_type value) { address_ = value; }
