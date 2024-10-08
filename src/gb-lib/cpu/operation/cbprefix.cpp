#include "cbprefix.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "location/location.h"

CbPrefix::CbPrefix(std::unique_ptr<InstructionDecoder>&& decoder)
    : realOp_()
    , decoder_(std::move(decoder))
{
}

void CbPrefix::nextOpcode(LocationUP opcode) { realOp_ = decoder_->decode(*opcode); }

auto CbPrefix::isComplete() -> bool { return static_cast<bool>(realOp_); }

auto CbPrefix::cycles() -> unsigned
{
  if (!isComplete()) {
    throw std::logic_error("Actual operation not yet set.");
  }
  return realOp_->cycles();
}

void CbPrefix::execute(RegistersInterface& registers, IMemoryView& memory)
{
  if (!isComplete()) {
    throw std::logic_error("Actual operation not yet set.");
  }
  realOp_->execute(registers, memory);
}
