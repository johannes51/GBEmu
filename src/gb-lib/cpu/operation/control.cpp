#include "control.h"

#include "../registers/flagsview.h"
#include "../registers/registersinterface.h"

Control::Control(ControlOp op)
    : op_(op)
{
}

void Control::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  (void)memory;
  switch (op_) {
  case ControlOp::EI:
    registers.getFlags().enableInterrupt();
    break;
  case ControlOp::DI:
    registers.getFlags().disableInterrupt();
    break;
  case ControlOp::Halt:
    registers.getFlags().halt();
    break;
  case ControlOp::Stop:
    throw std::logic_error("Stop unimplemented.");
    break;
  case ControlOp::Nop:
  default:
    break;
  }
}
