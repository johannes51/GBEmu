#ifndef HELPERS_H
#define HELPERS_H

#include "location/location.h"
#include "mem/mem_defines.h"

namespace hlp {

constexpr address_type ZeroPageBase = 0xFF00;

address_type indirect(const Location<address_type> location);
address_type indirect(const Location<uint8_t> location);

} // namespace hlp

#endif // HELPERS_H
