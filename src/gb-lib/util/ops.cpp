#include "ops.h"

#include "location.h"


Operation ops::toOperation(Location<uint16_t> &&location)
{
  return Operation(location.operator *());
}
