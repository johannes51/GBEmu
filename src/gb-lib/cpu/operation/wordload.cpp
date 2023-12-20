#include "wordload.h"

#include <stdexcept>

#include "cpu/registersinterface.h"
#include "location/location.h"
#include "location/variablebyte.h"
#include "mem/imemoryview.h"
#include "ops/arithmetic.h"
#include "ops/memory.h"
#include "util/helpers.h"

WordLoad::WordLoad(Destination destination, Source source)
    : destination_(destination)
    , source_(source)
{
}

WordLoad::~WordLoad() = default;

void WordLoad::nextOpcode(Location<uint8_t> opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate8_) {
    immediate8_.emplace(std::move(opcode));
  } else {
    immediate16_.emplace(Location<uint8_t>::fuse(std::move(*immediate8_), std::move(opcode)));
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
  } else if (destination_ == Destination::Stack) {
    result = BaseDuration + 1;
  } else if (source_ == Source::RegisterImmediate) {
    result = RegisterImmediateDuration + ((destRegister_ == WordRegister::SP) ? 1 : 0);
  }
  return result;
}

void WordLoad::execute(RegistersInterface& registers, IMemoryView& memory)
{
  auto sp = registers.get(WordRegister::SP);
  Location<uint16_t> destLoc;
  switch (destination_) {
  case Destination::Register:
    destLoc = registers.get(destRegister_);
    break;
  case Destination::ImmediateIndirect:
    if (!immediate16_) {
      throw std::invalid_argument("No immediate value configured");
    }
    destLoc = memory.getWord(hlp::indirect(*immediate16_));
    break;
  case Destination::RegisterIndirect:
    destLoc = memory.getWord(hlp::indirect(registers.get(destRegister_)));
    break;
  case Destination::Stack:
    ops::decrement(sp);
    ops::decrement(sp);
    destLoc = memory.getWord(hlp::indirect(sp));
    break;
  }
  Location<uint16_t> srcLoc;
  switch (source_) {
  case Source::Immediate:
    if (!immediate16_) {
      throw std::invalid_argument("No immediate value configured");
    }
    srcLoc = std::move(*immediate16_);
    break;
  case Source::Register:
    srcLoc = registers.get(srcRegister_);
    break;
  case Source::Stack:
    srcLoc = memory.getWord(hlp::indirect(registers.get(WordRegister::SP)));
    break;
  case Source::RegisterImmediate:
    srcLoc = registers.get(WordRegister::SP);
    break;
  }
  ops::load(destLoc, srcLoc);
  if (source_ == Source::Stack) {
    ops::increment(sp);
    ops::increment(sp);
  } else if (source_ == Source::RegisterImmediate) {
    if (!immediate8_) {
      throw std::invalid_argument("No immediate value configured");
    }
    ops::addSigned(destLoc, *immediate8_);
  }
}
