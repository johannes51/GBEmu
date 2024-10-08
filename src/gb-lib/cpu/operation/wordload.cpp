#include "wordload.h"

#include <stdexcept>

#include "cpu/registersinterface.h"
#include "location/location.h"
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

void WordLoad::nextOpcode(LocationUP opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate_) {
    immediate_ = std::move(opcode);
  } else if (!immediate_->isWord()) {
    immediate_->fuse(*opcode);
  }
}

auto WordLoad::isComplete() -> bool
{
  if (source_ == Source::Immediate || destination_ == Destination::ImmediateIndirect) {
    return static_cast<bool>(immediate_) && immediate_->isWord();
  } else if (source_ == Source::RegisterImmediate) {
    return static_cast<bool>(immediate_);
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
  LocationUP destLoc;
  switch (destination_) {
  case Destination::Register:
    destLoc = registers.get(destRegister_);
    break;
  case Destination::ImmediateIndirect:
    if (!immediate_) {
      throw std::invalid_argument("No immediate value configured");
    }
    destLoc = memory.getLocation(hlp::indirect(*immediate_));
    break;
  case Destination::RegisterIndirect:
    destLoc = memory.getLocation(hlp::indirect(*registers.get(destRegister_)));
    break;
  }
  LocationUP srcLoc;
  switch (source_) {
  case Source::Immediate:
    if (!immediate_) {
      throw std::invalid_argument("No immediate value configured");
    }
    srcLoc = std::move(immediate_);
    break;
  case Source::Register:
    srcLoc = registers.get(srcRegister_);
    break;
  case Source::RegisterImmediate:
    srcLoc = registers.get(WordRegister::SP);
    break;
  }
  ops::load<uint16_t>(*destLoc, *srcLoc);
  if (source_ == Source::RegisterImmediate) {
    if (!immediate_) {
      throw std::invalid_argument("No immediate value configured");
    }
    ops::addSigned(*destLoc, *immediate_);
  }
}
