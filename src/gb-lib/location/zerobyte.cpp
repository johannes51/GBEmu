#include "zerobyte.h"

auto ZeroByte::get() const -> uint8_t { return 0; }

void ZeroByte::set(const uint8_t& value) { (void)value; }
