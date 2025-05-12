#include "cpu.h"

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
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

auto Cpu::clock() -> bool
{
  if (!nextOperation_) {
    nextOperation_ = loadNextOperation();
  }

  if (--ticksTillExecution_ == 0) {
    nextOperation_->execute(*registers_, *mem_);
    *registers_->get(ByteRegister::F)
        = registers_->get(ByteRegister::F)->get() & UPPER_HALF_BYTE_MASK; // NOTE: this is so dumb
    if (executingInterrupt_) {
      interruptHandler_ = InterruptHandlerUP { dynamic_cast<InterruptHandler*>(nextOperation_.release()) };
      executingInterrupt_ = false;
      return false;
    } else {
      nextOperation_.reset();
      return true;
    }
  } else {
    return false;
  }
}

auto Cpu::loadNextOperation() -> OperationUP
{
  OperationUP result;
  if (registers_->getFlags().interruptEnabled() && interruptHandler_->isInterrupt()) {
    result = OperationUP { static_cast<Operation*>(interruptHandler_.release()) };
    executingInterrupt_ = true;
    registers_->getFlags().disableInterrupt();
  } else {
    const auto next = fetchNextOpcode();
    result = instructionDecoder_->decode(*next);
  }
  if (result) {
    result->showFlags(registers_->getFlags());
    while (!result->isComplete()) {
      auto next = fetchNextOpcode();
      result->nextOpcode(std::move(next));
    }
    ticksTillExecution_ = result->cycles();
  }
  return result;
}

auto Cpu::fetchNextOpcode() -> Location8UP
{
  auto pc = registers_->get(WordRegister::PC);
  auto result = mem_->getLocation8(hlp::indirect(*pc));
  ops::increment(*pc);
  return result;
}
