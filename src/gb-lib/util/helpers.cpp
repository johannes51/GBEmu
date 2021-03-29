#include "helpers.h"

auto hlp::indirect(const Location<address_type> location) -> address_type { return location.get(); }

address_type hlp::indirect(const Location<uint8_t> location) { return ZeroPageBase + location.get(); }
