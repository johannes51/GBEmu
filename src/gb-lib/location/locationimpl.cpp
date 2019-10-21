#include "locationimpl.h"

#include "locationbyte.h"

LocationImpl::LocationImpl(LocationByteUP lower, LocationByteUP upper)
    : lower_(std::move(lower)), upper_(std::move(upper)) {}

uint8_t LocationImpl::getByte() const { return **lower_; }

uint16_t LocationImpl::getWord() const {
  uint16_t result =
      (static_cast<uint16_t>(**upper_) << 8) | static_cast<uint16_t>(**lower_);
  return result;
}

void LocationImpl::setByte(uint8_t value) { *lower_ << value; }

void LocationImpl::setWord(uint16_t value) {
  uint8_t lowerValue = value & 0xFF;
  uint8_t upperValue = (value & 0xFF00) >> 8;
  *lower_ << lowerValue;
  *upper_ << upperValue;
}
