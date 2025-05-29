#ifndef LOGIC_H
#define LOGIC_H

#include "ops.h"

class ILocation8;

namespace ops {

OpResult andF(ILocation8& destination, const ILocation8& source);

OpResult orF(ILocation8& destination, const ILocation8& source);

OpResult xorF(ILocation8& destination, const ILocation8& source);

OpResult cpF(ILocation8& destination, const ILocation8& source);

} // namespace ops

#endif // LOGIC_H
