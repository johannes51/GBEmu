#include "cpu.h"

#include <cassert>

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "operation/operation.h"
#include "registersinterface.h"
#include "util/helpers.h"
#include "util/ops.h"

Cpu::Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem)
    : mem_(std::move(mem))
    , registers_(std::move(registers))
    , nextOperation_(nullptr)
{
}

Cpu::~Cpu() = default;

void Cpu::clock()
{
  if (!nextOperation_) {
    nextOperation_ = id::decode(nextOpcode());
    while (!nextOperation_->isComplete()) {
      nextOperation_->nextOpcode(nextOpcode());
    }
  }
  nextOperation_->clock();
  if (nextOperation_->isDone()) {
    nextOperation_->execute(*registers_);
    nextOperation_.reset();
  }
}

Location<uint8_t> Cpu::nextOpcode()
{
  auto result = mem_->getByte(hlp::indirect(registers_->get(WordRegisters::PC)));
  ops::increment(registers_->get(WordRegisters::PC));
  return result;
}
