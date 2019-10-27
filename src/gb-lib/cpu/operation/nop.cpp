#include "nop.h"

void Nop::executeImpl(RegistersInterface& registers, IMemoryView& memory)
{
  (void)registers;
  (void)memory;
}
