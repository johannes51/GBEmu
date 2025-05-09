#include "helpers.h"

auto hlp::indirect(const Location16& location) -> address_type { return location.get(); }

auto hlp::indirectZeroPage(const Location8& location) -> address_type { return ZERO_PAGE_BASE + location.get(); }
