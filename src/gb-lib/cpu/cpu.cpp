#include "cpu.h"

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "operation/operation.h"
#include "ops/arithmetic.h"
#include "registersinterface.h"
#include "util/helpers.h"

Cpu::Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem, InstructionDecoderUP instructionDecoder,
    InterruptHandlerUP interruptHandler)
    : mem_(std::move(mem))
    , registers_(std::move(registers))
    , instructionDecoder_(std::move(instructionDecoder))
    , interruptHandler_(std::move(interruptHandler))
{
}

Cpu::~Cpu() = default;

void Cpu::clock()
{
  if (!nextOperation_) {
    if (registers_->getFlags().interruptEnabled() && interruptHandler_->isInterrupt()) {
      nextOperation_ = OperationUP { static_cast<Operation*>(interruptHandler_.release()) };
      executingInterrupt_ = true;
      registers_->getFlags().disableInterrupt();
    } else {
      const auto next = nextOpcode();
      nextOperation_ = instructionDecoder_->decode(*next);
    }
    nextOperation_->showFlags(registers_->getFlags());
    while (!nextOperation_->isComplete()) {
      auto next = nextOpcode();
      nextOperation_->nextOpcode(std::move(next));
    }
    ticksTillExecution_ = nextOperation_->cycles();
  }
  --ticksTillExecution_;
  if (ticksTillExecution_ == 0) {
    nextOperation_->execute(*registers_, *mem_);
    if (executingInterrupt_) {
      interruptHandler_ = InterruptHandlerUP { dynamic_cast<InterruptHandler*>(nextOperation_.release()) };
      executingInterrupt_ = false;
    } else {
      nextOperation_.reset();
    }
  }
}

auto Cpu::nextOpcode() -> LocationUP
{
  auto pc = registers_->get(WordRegister::PC);
  auto result = mem_->getLocation(hlp::indirect(*pc));
  ops::increment<uint16_t>(*pc);
  return result;
}
