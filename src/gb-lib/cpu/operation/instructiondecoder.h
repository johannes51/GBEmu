#ifndef INSTRUCTIONDECODER_H
#define INSTRUCTIONDECODER_H

#include "cpu/cpu_defines.h"
#include "location/location_defines.h"

namespace id {

OperationUP decode(LocationUP<uint8_t> opcodeLocation);

}

#endif // INSTRUCTIONDECODER_H
