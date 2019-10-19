#include "ops.h"

#include "location/location.h"


Operation ops::toOperation(LocationUP<uint8_t>&& location)
{
  return Operation(**location);
}
