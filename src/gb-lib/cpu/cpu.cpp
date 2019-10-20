#include "cpu.h"

#include "registersinterface.h"
#include "mem/imemoryview.h"
#include "location/location.h"
#include "util/helpers.h"
#include "util/ops.h"
#include "operation.h"


Cpu::Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem)
  : registers_(std::move(registers))
  , mem_(mem)
  , nextOperation_(nullptr)
{
}

Cpu::~Cpu() = default;

void Cpu::clock()
{
  if (!nextOperation_) {
    nextOperation_ = std::make_unique<Operation>();
    while (nextOperation_->nextOpcode(**mem_->getByte(hlp::indirect(registers_->pc())))) {
      ops::increment(registers_->pc());
    }
  }
  nextOperation_->clock();
  if (nextOperation_->isDone()) {
  }
}

