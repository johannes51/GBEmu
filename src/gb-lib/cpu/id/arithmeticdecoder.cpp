#include "arithmeticdecoder.h"

#include <stdexcept>

#include "cpu/id/opcodeview.h"
#include "cpu/operation/aluoperation.h"

auto sourceRegister(const OpcodeView& opcode) -> ByteRegisters
{
  ByteRegisters result;
  switch (opcode.lowerNibble()) {
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

auto bulkArithmetic(const OpcodeView& opcode) -> OperationUP
{
  auto op = std::make_unique<AluOperation>(AluFunction::Xor, Source::Register);
  op->setRegister(sourceRegister(opcode));
  return op; // TODO: this is terrible
  //  throw std::logic_error("Unimplemented");
}

// return std::make_unique<AluOperation>(AluFunction::Dec, Source::None);

auto ArithmeticDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() >= 0x8 && opcode.upperNibble() <= 0xB) {
    return bulkArithmetic(opcode);
  }
  throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcodeLocation.get()) };
}

auto ArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91,
          0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3,
          0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5,
          0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF });
  return result;
}
