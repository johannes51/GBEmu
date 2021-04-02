#include "helpers.h"

auto hlp::indirect(const Location<address_type>& location) -> address_type { return location.get(); }

auto hlp::indirect(const Location<uint8_t>& location) -> address_type { return ZeroPageBase + location.get(); }
