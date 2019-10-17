#include "ops.h"

#include "location.h"


Operation ops::toOperation(Location<uint8_t>&& location)
{
  return Operation(location.operator *());
}
