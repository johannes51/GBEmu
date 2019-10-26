#include "loads.h"

#include "../operation/operation.h"

OperationUP id::loads::bulkLoad(const OpcodeView opcode)
{
  (void)opcode;
  throw std::logic_error("Unimplemented");
}
