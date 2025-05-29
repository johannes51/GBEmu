#include "helpers.h"

auto hlp::indirect(const ILocation16& location) -> address_type { return location.get(); }

auto hlp::indirectZeroPage(const ILocation8& location) -> address_type { return ZERO_PAGE_BASE + location.get(); }
