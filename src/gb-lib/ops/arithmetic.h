#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <limits>

#include "constants.h"
#include "mem/location16.h"
#include "mem/location8.h"
#include "ops.h"

namespace ops {

OpResult increment(Location8& location);
OpResult increment(Location16& location);

OpResult decrement(Location8& location);
OpResult decrement(Location16& location);

OpResult add(Location8& a, const Location8& b);
OpResult add_carry(Location8& a, const Location8& b, const bool carryFlag);
OpResult add(Location16& a, const Location16& b);
OpResult addSigned(Location16& a, const uint8_t bUnsigned);

OpResult sub(Location8& a, const Location8& b);
OpResult sub_carry(Location8& a, const Location8& b, const bool carryFlag);

OpResult complement(Location8& operand);

OpResult decimalAdjust(Location8& operand, const bool carry, const bool halfCarry, const bool subtract);

} // namespace ops

#endif // ARITHMETIC_H
