#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <limits>

#include "constants.h"
#include "location/location16.h"
#include "location/location8.h"
#include "ops.h"

namespace ops {

OpResult increment(Location8& location);
OpResult increment(Location16& location);

OpResult decrement(Location8& location);
OpResult decrement(Location16& location);

OpResult add(Location8& a, const Location8& b);
OpResult add(Location16& a, const Location16& b);
OpResult addSigned(Location16& a, const Location8& bUnsigned);

OpResult sub(Location8& a, const Location8& b);

OpResult complement(Location8& operand);

OpResult decimalAdjust(Location8& operand);

} // namespace ops

#endif // ARITHMETIC_H
