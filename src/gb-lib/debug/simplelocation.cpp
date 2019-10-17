#include "simplelocation.h"

#include <stdexcept>


SimpleLocation::SimpleLocation()
{
}

uint8_t SimpleLocation::operator *()
{
  throw std::logic_error("bla");
}
