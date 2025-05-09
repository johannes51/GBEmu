#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

class Location8;

namespace ops {

OpResult andF(Location8& destination, const Location8& source);

OpResult orF(Location8& destination, const Location8& source);

OpResult xorF(Location8& destination, const Location8& source);

OpResult cpF(Location8& destination, const Location8& source);

} // namespace ops

#endif // LOGIC_H
