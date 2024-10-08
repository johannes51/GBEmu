#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

class Location;

namespace ops {

OpResult andF(Location& destination, const Location& source);

OpResult orF(Location& destination, const Location& source);

OpResult xorF(Location& destination, const Location& source);

OpResult cpF(Location& destination, const Location& source);

} // namespace ops

#endif // LOGIC_H
