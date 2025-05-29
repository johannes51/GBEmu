#include "wordload.h"

#include <stdexcept>

#include "../registers/registersinterface.h"
#include "mem/common/fusedlocation16.h"
#include "mem/ilocation8.h"
#include "mem/imemoryview.h"
#include "mem/rest/variablelocation.h"
#include "ops/arithmetic.h"
#include "util/helpers.h"

WordLoad::WordLoad(Destination destination, Source source)
    : destination_(destination)
    , source_(source)
{
}

WordLoad::~WordLoad() = default;

void WordLoad::nextOpcode(const ILocation8& opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediateL_ && !immediateH_) {
    immediateL_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  } else if (!immediateH_) {
    immediateH_ = std::make_unique<VariableLocation8>(variableLocation(opcode.get()));
  }
}

auto WordLoad::isComplete() -> bool
{
  if (source_ == Source::Immediate || destination_ == Destination::ImmediateIndirect) {
    return static_cast<bool>(immediateL_) && static_cast<bool>(immediateH_);
  } else if (source_ == Source::RegisterImmediate) {
    return static_cast<bool>(immediateL_);
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

void WordLoad::execute(RegistersInterface& registers, IMemoryWordView& memory)
{
  auto immediate16 = FusedLocation16::construct(immediateL_.get(), immediateH_.get());
  ILocation16* destLoc = nullptr;
  switch (destination_) {
  case Destination::Register:
    destLoc = &registers.get(destRegister_);
    break;
  case Destination::ImmediateIndirect:
    if (!static_cast<bool>(immediateL_) && !static_cast<bool>(immediateH_)) {
      throw std::invalid_argument("No immediate value configured");
    }
    destLoc = &memory.getLocation16(hlp::indirect(immediate16));
    break;
  case Destination::RegisterIndirect:
    destLoc = &memory.getLocation16(hlp::indirect(registers.get(destRegister_)));
    break;
  }
  ILocation16* srcLoc = nullptr;
  switch (source_) {
  case Source::Immediate:
    if (!static_cast<bool>(immediateL_) && !static_cast<bool>(immediateH_)) {
      throw std::invalid_argument("No immediate value configured");
    }
    srcLoc = &immediate16;
    break;
  case Source::Register:
    srcLoc = &registers.get(srcRegister_);
    break;
  case Source::RegisterImmediate:
    srcLoc = &registers.get(WordRegister::SP);
    break;
  }
  *destLoc = srcLoc->get();
  if (source_ == Source::RegisterImmediate) {
    if (!immediateL_) {
      throw std::invalid_argument("No immediate value configured");
    }
    apply(registers.getFlags(), ops::addSigned(*destLoc, immediateL_->get()));
  }
}
