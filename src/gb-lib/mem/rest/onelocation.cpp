#include "onelocation.h"

uint8_t OneLocation::one_ = { 0xFFU };

const uint8_t& OneLocation::get() const { return one_; }

void OneLocation::set(const uint8_t& value) { (void)value; }

ByteLocationAdapterUP OneLocation::copy() { return std::make_unique<OneLocation>(); }
