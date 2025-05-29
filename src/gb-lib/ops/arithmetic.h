#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <limits>

#include "constants.h"
#include "mem/ilocation16.h"
#include "mem/ilocation8.h"
#include "ops.h"

namespace ops {

OpResult increment(ILocation8& location);
OpResult increment(ILocation16& location);

OpResult decrement(ILocation8& location);
OpResult decrement(ILocation16& location);

OpResult add(ILocation8& a, const ILocation8& b);
OpResult add_carry(ILocation8& a, const ILocation8& b, const bool carryFlag);
OpResult add(ILocation16& a, const ILocation16& b);
OpResult addSigned(ILocation16& a, const uint8_t bUnsigned);

OpResult sub(ILocation8& a, const ILocation8& b);
OpResult sub_carry(ILocation8& a, const ILocation8& b, const bool carryFlag);

OpResult complement(ILocation8& operand);

OpResult decimalAdjust(ILocation8& operand, const bool carry, const bool halfCarry, const bool subtract);

} // namespace ops

#endif // ARITHMETIC_H
