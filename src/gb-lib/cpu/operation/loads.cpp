#include "loads.h"

#include "operation.h"

OperationUP ops::bulkLoad(const OpcodeView opcode)
{
  (void)opcode;
  throw std::logic_error("Unimplemented");
}
