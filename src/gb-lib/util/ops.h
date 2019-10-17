#ifndef OPS_H
#define OPS_H

#include "cpu/operation.h"
#include "mem/mem_defines.h"
#include "util/util_defines.h"


namespace ops
{

Operation toOperation(LocationUP<uint8_t> &&location);

}

#endif // OPS_H
