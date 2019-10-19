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
  auto a = std::move(registers_->pc());
  auto b = hlp::indirect(a);
  auto c = mem_->getByte(b);
  auto nextOperation = ops::toOperation(std::move(c));
  if (nextOperation.lowerNibble() >= 0x4 && nextOperation.lowerNibble() < 0x7) {
    decodeLoad(nextOperation);
  }
}

void Cpu::decodeLoad(const Operation& operation)
{
  throw false;
}
