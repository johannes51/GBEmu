#include "arithmetic.h"

#include <stdexcept>

#include "../operation/aluoperation.h"

auto sourceRegister(const uint8_t lowerNibble) -> ByteRegisters
{
  ByteRegisters result;
  switch (lowerNibble) {
  case 0x0:
  case 0x8:
    result = ByteRegisters::B;
    break;
  case 0x1:
  case 0x9:
    result = ByteRegisters::C;
    break;
  case 0x2:
  case 0xA:
    result = ByteRegisters::D;
    break;
  case 0x3:
  case 0xB:
    result = ByteRegisters::E;
    break;
  case 0x4:
  case 0xC:
    result = ByteRegisters::H;
    break;
  case 0x5:
  case 0xD:
    result = ByteRegisters::L;
    break;
  case 0x7:
  case 0xF:
  default:
    result = ByteRegisters::A;
    break;
  }
  return result;
}

auto id::arithmetic::bulkArithmetic(const OpcodeView opcode) -> OperationUP
{
  if (opcode.upperNibble() >= 0x8 && opcode.upperNibble() <= 0xB) {
    auto op = std::make_unique<AluOperation>(AluFunction::Xor, Source::Register);
    op->setRegister(sourceRegister(opcode.lowerNibble()));
    return op;
  }
  throw std::logic_error("Unimplemented");
}

auto id::arithmetic::decrement(const OpcodeView opcode) -> OperationUP
{
  (void)opcode;
  return std::make_unique<AluOperation>(AluFunction::Dec, Source::None);
}
