#include "wordload.h"

#include <stdexcept>

#include "cpu/registersinterface.h"
#include "mem/common/fusedlocation16.h"
#include "mem/imemoryview.h"
#include "mem/location8.h"
#include "mem/rest/variablelocation.h"
#include "ops/arithmetic.h"
#include "util/helpers.h"

WordLoad::WordLoad(Destination destination, Source source)
    : destination_(destination)
    , source_(source)
{
}

WordLoad::~WordLoad() = default;

void WordLoad::nextOpcode(const Location8& opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate8_ && !immediate16_) {
    immediate8_ = std::make_unique<Location8>(variableLocation(opcode.get()));
  } else if (!immediate16_) {
    immediate16_ = std::make_unique<Location16>(FusedLocation16::construct(
        std::move(*immediate8_), variableLocation(opcode.get())));
  }
}

auto WordLoad::isComplete() -> bool
{
  if (source_ == Source::Immediate || destination_ == Destination::ImmediateIndirect) {
    return static_cast<bool>(immediate16_);
  } else if (source_ == Source::RegisterImmediate) {
    return static_cast<bool>(immediate8_);
  } else {
    return true;
  }
}

void WordLoad::setDestination(WordRegister destRegister) { destRegister_ = destRegister; }

void WordLoad::setSource(WordRegister srcRegister) { srcRegister_ = srcRegister; }

auto WordLoad::cycles() -> unsigned
{
  auto result = BaseDuration;
  if (destination_ == Destination::ImmediateIndirect) {
    result = ImmediateIndirectDuration;
  } else if (source_ == Source::Register && destination_ == Destination::Register) {
    result = BaseDuration - 1;
  } else if (source_ == Source::RegisterImmediate) {
    result = RegisterImmediateDuration + ((destRegister_ == WordRegister::SP) ? 1 : 0);
  }
  return result;
}

void WordLoad::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto sp = registers.get(WordRegister::SP);
  Location16 destLoc {};
  switch (destination_) {
  case Destination::Register:
    destLoc = registers.get(destRegister_);
    break;
  case Destination::ImmediateIndirect:
    if (!immediate16_) {
      throw std::invalid_argument("No immediate value configured");
    }
    destLoc = memory.getLocation16(hlp::indirect(*immediate16_));
    break;
  case Destination::RegisterIndirect:
    destLoc = memory.getLocation16(hlp::indirect(registers.get(destRegister_)));
    break;
  }
  Location16 srcLoc {};
  switch (source_) {
  case Source::Immediate:
    if (!immediate16_) {
      throw std::invalid_argument("No immediate value configured");
    }
    srcLoc = std::move(*immediate16_);
    immediate16_.reset();
    break;
  case Source::Register:
    srcLoc = registers.get(srcRegister_);
    break;
  case Source::RegisterImmediate:
    srcLoc = registers.get(WordRegister::SP);
    break;
  }
  destLoc = srcLoc.get();
  if (source_ == Source::RegisterImmediate) {
    if (!immediate8_) {
      throw std::invalid_argument("No immediate value configured");
    }
    apply(registers.getFlags(), ops::addSigned(destLoc, immediate8_->get()));
  }
}
