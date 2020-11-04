#include "wordload.h"

#include <stdexcept>

#include "../registersinterface.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

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

bool WordLoad::isComplete()
{
  bool result = true;
  if (source_ == Source::Immediate || destination_ == Destination::ImmediateIndirect) {
    result = static_cast<bool>(immediate16_);
  }
  return result;
}

void WordLoad::setDestination(WordRegisters destRegister) { destRegister_ = destRegister; }

void WordLoad::setSource(WordRegisters srcRegister) { srcRegister_ = srcRegister; }

unsigned int WordLoad::cycles()
{
  auto result = 3U;
  if (destination_ == Destination::ImmediateIndirect) {
    result = 5U;
  }
  return result;
}

void WordLoad::execute(RegistersInterface& registers, IMemoryView& memory)
{
  Location<uint16_t> destination;
  if (destination_ == Destination::Register) {
    destination = registers.get(destRegister_);
  } else {
    address_type address;
    if (destination_ == Destination::RegisterIndirect) {
      address = hlp::indirect(registers.get(destRegister_));
    } else {
      address = hlp::indirect(std::move(*immediate16_));
    }
    destination = memory.getWord(address);
  }
  Location<uint16_t> source;
  if (source_ == Source::Register) {
    source = registers.get(srcRegister_);
  } else {
    source = std::move(*immediate16_);
  }
  ops::load(std::move(destination), std::move(source));
}
