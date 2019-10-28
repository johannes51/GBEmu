#include "nop.h"

void Nop::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)registers;
  (void)memory;
}
