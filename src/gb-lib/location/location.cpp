#include "location.h"


template<>
uint8_t Location<uint8_t>::operator *() const
{
  return getByte();
}

template<>
uint16_t Location<uint16_t>::operator *() const
{
  return getWord();
}

template<>
Location<uint8_t>& Location<uint8_t>::operator <<(const uint8_t& value)
{
  setByte(value);
  return *this;
}

template<>
Location<uint16_t>& Location<uint16_t>::operator <<(const uint16_t& value)
{
  setWord(value);
  return *this;
}

