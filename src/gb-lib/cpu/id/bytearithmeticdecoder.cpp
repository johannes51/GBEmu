#include "bytearithmeticdecoder.h"

#include <stdexcept>

#include "cpu/id/opcodeview.h"
#include "cpu/operation/bytealuoperation.h"

auto sourceRegister(const OpcodeView& opcode) -> ByteRegister
{
  ByteRegister result;
  switch (opcode.lowerNibble()) {
  case 0x0:
  case 0x8:
    result = ByteRegister::B;
    break;
  case 0x1:
  case 0x9:
    result = ByteRegister::C;
    break;
  case 0x2:
  case 0xA:
    result = ByteRegister::D;
    break;
  case 0x3:
  case 0xB:
    result = ByteRegister::E;
    break;
  case 0x4:
  case 0xC:
    result = ByteRegister::H;
    break;
  case 0x5:
  case 0xD:
    result = ByteRegister::L;
    break;
  case 0x7:
  case 0xF:
  default:
    result = ByteRegister::A;
    break;
  }
  return result;
}

auto function(const OpcodeView& opcode) -> ByteAluFunction
{
  if (opcode.lowerNibble() <= 0x7) {
    switch (opcode.upperNibble()) {
    case 0x8:
      return ByteAluFunction::Add;
      break;
    case 0x9:
      //      return AluFunction::Sub;
    case 0xA:
      //      return AluFunction::And;
    case 0xB:
      return ByteAluFunction::Or;
    default:
      throw std::logic_error("Unimplemented");
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x8:
      //      return AluFunction::AddCarry;
    case 0x9:
      //      return AluFunction::SubCarry;
      throw std::logic_error("Unimplemented");
      break;
    case 0xA:
      return ByteAluFunction::Xor;
      break;
    case 0xB:
      //      return AluFunction::Compare;
    default:
      throw std::logic_error("Unimplemented");
      break;
    }
  }
}

auto bulkArithmetic(const OpcodeView& opcode) -> OperationUP
{
  auto op = std::make_unique<ByteAluOperation>(function(opcode), Source::Register);
  op->setRegister(sourceRegister(opcode));
  return op;
}

auto incDec(const OpcodeView& opcode) -> OperationUP
{
  auto function
      = opcode.lowerNibble() == 0x4 || opcode.lowerNibble() == 0xC ? ByteAluFunction::Inc : ByteAluFunction::Dec;
  auto source = (opcode.lowerNibble() == 0x4 || opcode.lowerNibble() == 0xC) && opcode.upperNibble() == 0x3
      ? Source::Indirect
      : Source::Register;
  auto result = std::make_unique<ByteAluOperation>(function, source);
  switch (opcode.value()) {
  case 0x04:
  case 0x05:
    result->setRegister(ByteRegister::B);
    break;
  case 0x14:
  case 0x15:
    result->setRegister(ByteRegister::D);
    break;
  case 0x24:
  case 0x25:
    result->setRegister(ByteRegister::H);
    break;
  case 0x0C:
  case 0x0D:
    result->setRegister(ByteRegister::C);
    break;
  case 0x1C:
  case 0x1D:
    result->setRegister(ByteRegister::E);
    break;
  case 0x2C:
  case 0x2D:
    result->setRegister(ByteRegister::L);
    break;
  case 0x3C:
  case 0x3D:
    result->setRegister(ByteRegister::A);
    break;
  default:
    break;
  }
  return result;
}

auto ByteArithmeticDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() >= 0x8 && opcode.upperNibble() <= 0xB) {
    return bulkArithmetic(opcode);
  } else if (opcode.upperNibble() <= 0x3
      && (opcode.lowerNibble() == 0x4 || opcode.lowerNibble() == 0x5 || opcode.lowerNibble() == 0xC
          || opcode.lowerNibble() == 0xD)) {
    return incDec(opcode);
  }
  throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcodeLocation.get()) };
}

auto ByteArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91,
          0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3,
          0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5,
          0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF }); // bulk arithmetic
  result.insert(result.end(),
      {
          0x04,
          0x14,
          0x24,
          0x34,
          0x05,
          0x15,
          0x25,
          0x35,
          0x0C,
          0x1C,
          0x2C,
          0x3C,
          0x0D,
          0x1D,
          0x2D,
          0x3D,
      }); // inc/dec
  return result;
}
