#include "helpers.h"

auto hlp::indirect(const Location<address_type> location) -> address_type { return location.get(); }
