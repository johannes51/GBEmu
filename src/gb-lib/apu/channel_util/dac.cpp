#include "dac.h"

auto DAC::getSample() const -> const double& { return sample_; }

void DAC::set(uint8_t digValue) { sample_ = 1.0 - (static_cast<double>(digValue) / DigitalHalfScale); }
