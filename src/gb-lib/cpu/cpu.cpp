#include "cpu.h"

#include "registersinterface.h"
#include "mem/imemoryview.h"
#include "location/location.h"
#include "util/helpers.h"
#include "util/ops.h"


Cpu::Cpu(RegistersInterfaceUP&& registers, const IMemoryViewSP &mem)
  : registers_(std::move(registers))
  , mem_(std::move(mem))
{
}

void Cpu::clock()
{
  Operation nextOperation{};
  while (nextOperation.nextOpcode(**mem_->getByte(hlp::indirect(registers_->pc())))) {
    ops::increment(registers_->pc());
  }
}

