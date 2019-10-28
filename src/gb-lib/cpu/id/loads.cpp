#include "loads.h"

#include "../operation/load.h"

std::pair<Destination, ByteRegisters> destination(const OpcodeView& opcode)
{
  auto destRegister = ByteRegisters::A;
  auto dest = Destination::Register8;
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
      dest = Destination::RegisterIndirect;
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

std::pair<Source, ByteRegisters> source(const OpcodeView& opcode)
{
  auto srcRegister = ByteRegisters::A;
  auto src = Source::Register;
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
    src = Source::RegisterIndirect;
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
  auto result = std::make_unique<Load>(opDestination.first, opSource.first);
  if (opDestination.first == Destination::Register8) {
    result->setDestination(opDestination.second);
  }
  if (opSource.first == Source::Register) {
    result->setSource(opSource.second);
  }
  return result;
}

OperationUP id::loads::loadImmediate(const OpcodeView opcode)
{
  std::unique_ptr<Load> result(nullptr);
  switch (opcode.value()) {
  case 0x06:
    result = std::make_unique<Load>(Destination::Register8, Source::Register);
    result->setDestination(ByteRegisters::H);
    result->setSource(ByteRegisters::B);
    break;
  case 0x0E:
    result = std::make_unique<Load>(Destination::Register8, Source::Immediate);
    result->setDestination(ByteRegisters::C);
    break;
  case 0x11:
    result = std::make_unique<Load>(Destination::Register16, Source::Immediate);
    result->setDestination(WordRegisters::DE);
    break;
  case 0x21:
    result = std::make_unique<Load>(Destination::Register16, Source::Immediate);
    result->setDestination(WordRegisters::HL);
    break;
  case 0x32:
    result = std::make_unique<Load>(Destination::Register16, Source::Immediate);
    result->setDestination(WordRegisters::SP);
    break;
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
  return result;
}
