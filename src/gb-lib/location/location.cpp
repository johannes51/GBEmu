#include "location.h"

bool Location::isWord() const { return (type_ == Type::Both); }

void Location::fuse(const Location& other)
{
  if ((type_ != Type::Both) && (&other.getByte() == (&getByte()) + 1)) {
    type_ = Type::Both;
  }
}

template <> auto Location::get<uint8_t>() const -> const uint8_t& { return getByte(); }

template <> auto Location::get<uint16_t>() const -> const uint16_t& { return getWord(); }
