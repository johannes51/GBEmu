#include "cpu.h"

#include "registersinterface.h"
#include "mem/memoryview.h"
#include "util/helpers.h"
#include "util/location.h"
#include "util/ops.h"


Cpu::Cpu(RegistersInterfaceUP&& registers, const MemoryViewSP &mem)
  : registers_(std::move(registers))
  , mem_(std::move(mem))
{
}

void Cpu::clock()
{
  auto a = std::move(registers_->sp());
  auto b = hlp::indirect(a);
  auto c = mem_->getByte(b);
  auto nextOperation = ops::toOperation(std::move(c));
  if (nextOperation.lowerNibble() >= 0x4 && nextOperation.lowerNibble() < 0x7) {
    decodeLoad(nextOperation);
  }
}

void Cpu::decodeLoad(const Operation& operation)
{
}
