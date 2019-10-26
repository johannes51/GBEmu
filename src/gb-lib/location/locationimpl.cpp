#include "locationimpl.h"

#include "locationbyte.h"

LocationImpl::LocationImpl(LocationByteUP lower, LocationByteUP upper)
    : lower_(std::move(lower))
    , upper_(std::move(upper))
{
}

uint8_t LocationImpl::getByte() const { return lower_->get(); }

uint16_t LocationImpl::getWord() const
{
  uint16_t result
      = static_cast<uint16_t>(static_cast<uint16_t>(upper_->get()) << BYTE_SIZE) | static_cast<uint16_t>(lower_->get());
  return result;
}

void LocationImpl::setByte(uint8_t value) { lower_->set(value); }

void LocationImpl::setWord(uint16_t value)
{
  uint8_t lowerValue = value & LOWER_MASK;
  uint8_t upperValue = static_cast<uint16_t>(value & UPPER_MASK) >> BYTE_SIZE;
  lower_->set(lowerValue);
  upper_->set(upperValue);
}
