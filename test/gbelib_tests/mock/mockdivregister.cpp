#include "mockdivregister.h"

std::array<uint8_t, 1U> buffer;

MockIoBank MockDivRegister::b_ = MockIoBank { buffer };
