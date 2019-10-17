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

