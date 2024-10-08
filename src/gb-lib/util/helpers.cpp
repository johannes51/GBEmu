#include "helpers.h"

auto hlp::indirectZeroPage(const Location& location) -> address_type { return ZeroPageBase + location.getByte(); }
