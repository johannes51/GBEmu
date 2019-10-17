#include "nullbyte.h"

#include <stdexcept>


uint8_t NullByte::operator *()
{
  throw std::logic_error("Read on null byte");
}
