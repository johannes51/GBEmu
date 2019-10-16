#include "operation.h"

Operation::Operation(uint8_t value)
  : value_(value)
  , lower_(value & 0x0F)
  , upper_((value & 0xF0) >> 4)
{
}


const uint8_t& Operation::lowerNibble()
{
  return lower_;
}

const uint8_t &Operation::upperNibble()
{
  return upper_;
}
