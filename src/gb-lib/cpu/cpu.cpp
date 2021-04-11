#include "cpu.h"

#include <cassert>

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "operation/operation.h"
#include "ops/arithmetic.h"
#include "registersinterface.h"
#include "util/helpers.h"

Cpu::Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem, InstructionDecoderUP instructionDecoder)
    : mem_(std::move(mem))
    , registers_(std::move(registers))
    , instructionDecoder_(std::move(instructionDecoder))
    , nextOperation_(nullptr)
{
}

Cpu::~Cpu() = default;

void Cpu::clock()
{
  if (!nextOperation_) {
    nextOperation_ = instructionDecoder_->decode(nextOpcode());
    while (!nextOperation_->isComplete()) {
      nextOperation_->nextOpcode(nextOpcode());
    }
    ticksTillExecution_ = nextOperation_->cycles(*registers_);
  }
  --ticksTillExecution_;
  if (ticksTillExecution_ <= 0) {
    nextOperation_->execute(*registers_, *mem_);
    nextOperation_.reset();
  }
}

auto Cpu::nextOpcode() -> Location<uint8_t>
{
  auto pc = registers_->get(WordRegister::PC);
  auto result = mem_->getByte(hlp::indirect(pc));
  ops::increment(pc);
  return result;
}
