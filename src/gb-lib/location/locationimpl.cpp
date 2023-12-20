#include "locationimpl.h"

#include "locationbyte.h"

LocationImpl::LocationImpl(LocationByteUP lower, LocationByteUP upper)
    : lower_(std::move(lower))
    , upper_(std::move(upper))
{
}

auto LocationImpl::getByte() const -> uint8_t { return lower_->get(); }

auto LocationImpl::getWord() const -> uint16_t
{
  return static_cast<uint16_t>(static_cast<uint16_t>(upper_->get()) << BYTE_SIZE)
      | static_cast<uint16_t>(lower_->get());
}

void LocationImpl::setByte(uint8_t value) { lower_->set(value); }

void LocationImpl::setWord(uint16_t value)
{
  lower_->set(value & LOWER_MASK);
  upper_->set(static_cast<uint16_t>(value & UPPER_MASK) >> BYTE_SIZE);
}
