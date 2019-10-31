#include "loads.h"

#include "../operation/byteload.h"
#include "../operation/wordload.h"

std::pair<ByteLoad::Destination, ByteRegisters> destination(const OpcodeView& opcode)
{
  auto destRegister = ByteRegisters::A;
  auto dest = ByteLoad::Destination::Register;
  if (opcode.lowerNibble() <= 0x7) {
    switch (opcode.upperNibble()) {
    case 0x4:
      destRegister = ByteRegisters::B;
      break;
    case 0x5:
      destRegister = ByteRegisters::D;
      break;
    case 0x6:
      destRegister = ByteRegisters::H;
      break;
    case 0x7:
      dest = ByteLoad::Destination::RegisterIndirect;
      break;
    default:
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x4:
      destRegister = ByteRegisters::C;
      break;
    case 0x5:
      destRegister = ByteRegisters::E;
      break;
    case 0x6:
      destRegister = ByteRegisters::L;
      break;
    case 0x7:
      destRegister = ByteRegisters::A;
    default:
      break;
    }
  }
  return std::make_pair(dest, destRegister);
}

std::pair<ByteLoad::Source, ByteRegisters> source(const OpcodeView& opcode)
{
  auto srcRegister = ByteRegisters::A;
  auto src = ByteLoad::Source::Register;
  switch (opcode.lowerNibble()) {
  case 0x0:
  case 0x8:
    srcRegister = ByteRegisters::B;
    break;
  case 0x1:
  case 0x9:
    srcRegister = ByteRegisters::C;
    break;
  case 0x2:
  case 0xA:
    srcRegister = ByteRegisters::D;
    break;
  case 0x3:
  case 0xB:
    srcRegister = ByteRegisters::E;
    break;
  case 0x4:
  case 0xC:
    srcRegister = ByteRegisters::H;
    break;
  case 0x5:
  case 0xD:
    srcRegister = ByteRegisters::L;
    break;
  case 0x6:
  case 0xE:
    src = ByteLoad::Source::RegisterIndirect;
    break;
  case 0x7:
  case 0xF:
    srcRegister = ByteRegisters::A;
    break;
  }
  return std::make_pair(src, srcRegister);
}

OperationUP id::loads::bulkLoad(const OpcodeView opcode)
{
  if (opcode.value() == 0x76) {
    throw std::logic_error("HALT unimplemented");
  }
  const auto opDestination = destination(opcode);
  const auto opSource = source(opcode);
  auto result = std::make_unique<ByteLoad>(opDestination.first, opSource.first);
  if (opDestination.first == ByteLoad::Destination::Register) {
    result->setDestination(opDestination.second);
  }
  if (opSource.first == ByteLoad::Source::Register) {
    result->setSource(opSource.second);
  }
  return result;
}

OperationUP id::loads::loadImmediate(const OpcodeView opcode)
{
  OperationUP result;
  switch (opcode.value()) {
  case 0x06: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::Immediate);
    p->setDestination(ByteRegisters::B);
    result = std::move(p);
    break;
  }
  case 0x0E: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::Immediate);
    p->setDestination(ByteRegisters::C);
    result = std::move(p);
    break;
  }
  case 0x11: {
    auto p = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Immediate);
    p->setDestination(WordRegisters::DE);
    result = std::move(p);
    break;
  }
  case 0x21: {
    auto p = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Immediate);
    p->setDestination(WordRegisters::HL);
    result = std::move(p);
    break;
  }
  case 0x32: {
    auto p = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Immediate);
    p->setDestination(WordRegisters::SP);
    result = std::move(p);
    break;
  }
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
  return result;
}

OperationUP id::loads::loadRegisterIndirect(const OpcodeView opcode, bool store)
{
  auto dest = store ? ByteLoad::Destination::RegisterIndirect : ByteLoad::Destination::Register;
  auto src = store ? ByteLoad::Source::Register : ByteLoad::Source::RegisterIndirect;
  auto result = std::make_unique<ByteLoad>(dest, src);
  WordRegisters indirectRegister = WordRegisters::HL;
  switch (opcode.upperNibble()) {
  case 0x0:
    indirectRegister = WordRegisters::BC;
    break;
  case 0x1:
    indirectRegister = WordRegisters::DE;
    break;
  case 0x2:
    indirectRegister = WordRegisters::HL;
    result->setPostAction(ByteLoad::Post::Increment);
    break;
  case 0x3:
    indirectRegister = WordRegisters::HL;
    result->setPostAction(ByteLoad::Post::Decrement);
    break;
  }
  if (store) {
    result->setDestination(indirectRegister);
    result->setSource(ByteRegisters::A);
  } else {
    result->setDestination(ByteRegisters::A);
    result->setSource(indirectRegister);
  }
  return result;
}
