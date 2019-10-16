#include "location.h"


template<>
uint8_t Location<uint8_t>::operator *() const
{
  return location_.getByte();
}

template<>
uint16_t Location<uint16_t>::operator *() const
{
  return location_.getWord();
}

template<>
Location<uint8_t>&& Location<uint8_t>::generate(LocationByte&& lower, LocationByte&& upper)
{
  return Location<uint8_t>(LocationImpl(std::move(lower), std::move(upper)));
}

