#include "byteload.h"

#include <stdexcept>

#include "../registersinterface.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

ByteLoad::ByteLoad(Destination destination, Source source, bool zeroPage)
    : destination_(destination)
    , source_(source)
    , zeroPage_(zeroPage)
{
}

ByteLoad::~ByteLoad() = default;

void ByteLoad::nextOpcode(Location<uint8_t> opcode)
{
  if (isComplete()) {
    throw std::logic_error("Already done");
  }
  if (!immediate8_) {
    immediate8_.emplace(std::move(opcode));
  } else {
    immediate16_.emplace(Location<uint8_t>::fuse(std::move(opcode), std::move(*immediate8_)));
  }
}

auto ByteLoad::isComplete() -> bool
{
  bool result = true;
  if (source_ == Source::ImmediateIndirect || destination_ == Destination::ImmediateIndirect) {
    if (zeroPage_) {
      result = static_cast<bool>(immediate8_);
    } else {
      result = static_cast<bool>(immediate16_);
    }
  } else if (source_ == Source::Immediate) {
    result = static_cast<bool>(immediate8_);
  }
  return result;
}

void ByteLoad::setDestination(ByteRegisters destRegister) { destRegister8_ = destRegister; }

void ByteLoad::setDestination(WordRegisters destRegister) { destRegister16_ = destRegister; }

void ByteLoad::setSource(ByteRegisters srcRegister) { srcRegister8_ = srcRegister; }

void ByteLoad::setSource(WordRegisters srcRegister) { srcRegister16_ = srcRegister; }

void ByteLoad::setPostAction(ByteLoad::Post postAction) { postAction_ = postAction; }

auto ByteLoad::cycles() -> unsigned int
{
  auto result = BaseDuration;
  switch (source_) {
  case Source::Immediate:
  case Source::RegisterIndirect:
    ++result;
    break;
  case Source::ImmediateIndirect:
    result += zeroPage_ ? 2 : 3;
    break;
  default:
    break;
  }
  switch (destination_) {
  case Destination::RegisterIndirect:
    ++result;
    break;
  case Destination::ImmediateIndirect:
    result += zeroPage_ ? 2 : 3;
    break;
  default:
    break;
  }
  return result;
}

void ByteLoad::execute(RegistersInterface& registers, IMemoryView& memory)
{
  Location<uint8_t> destination;
  if (destination_ == Destination::Register) {
    destination = registers.get(destRegister8_);
  } else {
    address_type address = 0;
    if (destination_ == Destination::RegisterIndirect) {
      address = hlp::indirect(registers.get(destRegister16_));
    } else {
      address = hlp::indirect(std::move(*immediate16_));
    }
    destination = memory.getByte(address);
  }
  Location<uint8_t> source;
  switch (source_) {
  case Source::Immediate:
    source = std::move(*immediate8_);
    break;
  case Source::ImmediateIndirect:
    source = zeroPage_ ? memory.getByte(hlp::indirect(std::move(*immediate8_)))
                       : memory.getByte(hlp::indirect(std::move(*immediate16_)));
    break;
  case Source::Register:
    source = registers.get(srcRegister8_);
    break;
  case Source::RegisterIndirect:
    source = memory.getByte(hlp::indirect(registers.get(srcRegister16_)));
    break;
  }
  ops::load(std::move(destination), std::move(source));
}
