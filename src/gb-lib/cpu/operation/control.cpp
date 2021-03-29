#include "control.h"

#include "cpu/flagsview.h"
#include "cpu/registersinterface.h"

Control::Control(ControlOp op)
    : op_(op)
{
}

void Control::execute(RegistersInterface& registers, IMemoryView& memory)
{
  (void)memory;
  switch (op_) {
  case ControlOp::EI:
    registers.getFlags().enableInterrupt();
    break;
  case ControlOp::DI:
    registers.getFlags().disableInterrupt();
    break;
  default:
    break;
  }
}