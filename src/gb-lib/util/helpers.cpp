#include "helpers.h"

#include "constants.h"

auto hlp::indirectZeroPage(const Location& location) -> address_type { return ZERO_PAGE_BASE + location.getByte(); }
