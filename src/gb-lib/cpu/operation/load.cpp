#include "load.h"

#include "../registersinterface.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "util/helpers.h"
#include "util/ops.h"

Load::Load(Destination destination, Source source)
    : immediate8_()
    , immediate16_()
    , destination_(destination)
    , source_(source)
    , destRegister8_(std::nullopt)
    , srcRegister8_(std::nullopt)
    , destRegister16_(std::nullopt)
    , srcRegister16_(std::nullopt)
{
}

Load::~Load() = default;

void Load::nextOpcode(Location<uint8_t> opcode)
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

bool Load::isComplete()
{
  bool result = true;
  if (source_ == Source::ImmediateIndirect || destination_ == Destination::ImmediateIndirect
      || (source_ == Source::Immediate && destination_ == Destination::Register16)) {
    result = static_cast<bool>(immediate16_);
  } else if (source_ == Source::Immediate) {
    result = static_cast<bool>(immediate8_);
  }
  return result;
}

void Load::setDestination(ByteRegisters destRegister) { destRegister8_ = destRegister; }

void Load::setDestination(WordRegisters destRegister) { destRegister16_ = destRegister; }

void Load::setSource(ByteRegisters srcRegister) { srcRegister8_ = srcRegister; }

void Load::setSource(WordRegisters srcRegister) { srcRegister16_ = srcRegister; }

uint Load::cycles()
{
  auto result = 1U;
  if (destination_ == Destination::ImmediateIndirect) {
    result = 5U;
  } else if (destination_ == Destination::RegisterIndirect || source_ == Source::RegisterIndirect) {
    ++result;
  }
  if (source_ == Source::Immediate) {
    if (destination_ == Destination::Register8 || destination_ == Destination::RegisterIndirect) {
      ++result;
    } else if (destination_ == Destination::Register16) {
      result += 2;
    }
  }
  return result;
}

void Load::execute(RegistersInterface& registers, IMemoryView& memory)
{
  Location<uint16_t> source16;
  Location<uint8_t> source8;
  switch (destination_) {
  case Destination::Register16:
    switch (source_) {
    case Source::Immediate:
      source16 = std::move(*immediate16_);
      break;
    case Source::ImmediateIndirect:
      source16 = memory.getWord(hlp::indirect(std::move(*immediate16_)));
      break;
    case Source::Register:
      source16 = registers.get(*destRegister16_);
      break;
    case Source::RegisterIndirect:
      source16 = memory.getWord(hlp::indirect(registers.get(*srcRegister16_)));
      break;
    }
    ops::load(registers.get(*destRegister16_), std::move(source16));
    break;
  case Destination::Register8:
  case Destination::RegisterIndirect:
    switch (source_) {
    case Source::Immediate:
      source8 = std::move(*immediate8_);
      break;
    case Source::Register:
      source8 = registers.get(*srcRegister8_);
      break;
    case Source::RegisterIndirect:
      source8 = memory.getByte(hlp::indirect(registers.get(WordRegisters::HL)));
      break;
    default:
      throw std::invalid_argument("Impossible combination of dest and source");
    }
    ops::load((destination_ == Destination::Register8)
            ? registers.get(*destRegister8_)
            : memory.getByte(hlp::indirect(registers.get(WordRegisters::HL))),
        std::move(source8));
    break;
  case Destination::ImmediateIndirect:
    ops::load(memory.getWord(hlp::indirect(std::move(*immediate16_))), registers.get(WordRegisters::SP));
  }
}
