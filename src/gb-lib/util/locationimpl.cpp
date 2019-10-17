#include "locationimpl.h"

LocationImpl::LocationImpl(LocationByte&& lower, LocationByte&& upper)
  : lower_(lower)
  ,upper_(upper)
{
}

uint8_t LocationImpl::getByte() const
{
  return 0;
}

uint16_t LocationImpl::getWord() const
{
  uint16_t result = *upper_;

  return 0;
}
