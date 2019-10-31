#include "byteload.h"

#include "../registersinterface.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

ByteLoad::ByteLoad(Destination destination, Source source)
    : destination_(destination)
    , source_(source)
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
    immediate16_.emplace(Location<uint8_t>::fuse(std::move(*immediate8_), std::move(opcode)));
  }
}

bool ByteLoad::isComplete()
{
  bool result = true;
  if (source_ == Source::ImmediateIndirect || destination_ == Destination::ImmediateIndirect) {
    result = static_cast<bool>(immediate16_);
  } else if (source_ == Source::Immediate) {
    result = static_cast<bool>(immediate8_);
  }
  return result;
}

void ByteLoad::setDestination(ByteRegisters destRegister) {
  destRegister8_ = destRegister;
}

void ByteLoad::setDestination(WordRegisters destRegister) {
  destRegister16_ = destRegister;
}

void ByteLoad::setSource(ByteRegisters srcRegister) {
  srcRegister8_ = srcRegister;
}

void ByteLoad::setSource(WordRegisters srcRegister) {
  srcRegister16_ = srcRegister;
}

void ByteLoad::setPostAction(ByteLoad::Post postAction) {
  postAction_ = postAction;
}

uint ByteLoad::cycles()
{
  auto result = 1U;
  if (destination_ == Destination::ImmediateIndirect) {
    result = 5U;
  } else if (destination_ == Destination::RegisterIndirect || source_ == Source::RegisterIndirect) {
    ++result;
  }
  if (source_ == Source::Immediate) {
    if (destination_ == Destination::Register || destination_ == Destination::RegisterIndirect) {
      ++result;
    } else if (destination_ == Destination::Register) {
      result += 2;
    }
  }
  return result;
}

void ByteLoad::execute(RegistersInterface& registers, IMemoryView& memory)
{
  Location<uint8_t> destination;
  if (destination_ == Destination::Register) {
    destination = registers.get(destRegister8_);
  } else {
    address_type address;
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
    source = memory.getByte(hlp::indirect(std::move(*immediate16_)));
    break;
  case Source::Register:
    source = registers.get(srcRegister8_);
    break;
  case Source::RegisterIndirect:
    source = memory.getByte(hlp::indirect(registers.get(srcRegister16_)));
    break;
  default:
    throw std::invalid_argument("Impossible combination of dest and source");
  }
  ops::load(std::move(destination), std::move(source));
}
