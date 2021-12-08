#include "cbprefix.h"

#include <stdexcept>

#include "cpu/id/cbopdecoder.h"
#include "location/location.h"

CbPrefix::CbPrefix(std::unique_ptr<InstructionDecoder>&& decoder)
    : realOp_()
    , decoder_(std::move(decoder))
{
}

void CbPrefix::nextOpcode(Location<uint8_t> opcode) { realOp_ = decoder_->decode(opcode); }

auto CbPrefix::isComplete() -> bool { return static_cast<bool>(realOp_); }

auto CbPrefix::cycles(const RegistersInterface& registers) -> unsigned
{
  if (!isComplete()) {
    throw std::logic_error("Actual operation not yet set.");
  }
  return realOp_->cycles(registers);
}

void CbPrefix::execute(RegistersInterface& registers, IMemoryView& memory)
{
  if (!isComplete()) {
    throw std::logic_error("Actual operation not yet set.");
  }
  return realOp_->execute(registers, memory);
}
