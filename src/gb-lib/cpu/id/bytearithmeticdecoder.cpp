#include "bytearithmeticdecoder.h"

#include <stdexcept>

#include "../operation/bytealuoperation.h"
#include "cpu/registersinterface.h"
#include "location/location8.h"

auto ByteArithmeticDecoder::decode(const Location8& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.get() };
  if (opcode.upperNibble() >= 0x8U && opcode.upperNibble() <= 0xBU) {
    return bulkArithmetic(opcode);
  } else if (opcode.upperNibble() <= 0x3U
      && (opcode.lowerNibble() == 0x4U || opcode.lowerNibble() == 0x5U || opcode.lowerNibble() == 0xCU
          || opcode.lowerNibble() == 0xDU)) {
    return incDec(opcode);
  } else if (opcode.upperNibble() >= 0xCU) {
    return immediate(opcode);
  }
  throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcodeLocation.get()) };
}

auto ByteArithmeticDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      {
          0x04U,
          0x14U,
          0x24U,
          0x34U,
          0x05U,
          0x15U,
          0x25U,
          0x35U,
          0x0CU,
          0x1CU,
          0x2CU,
          0x3CU,
          0x0DU,
          0x1DU,
          0x2DU,
          0x3DU,
      }); // inc/dec
  result.insert(result.end(),
      { 0x80U, 0x81U, 0x82U, 0x83U, 0x84U, 0x85U, 0x86U, 0x87U, 0x88U, 0x89U, 0x8AU, 0x8BU, 0x8CU, 0x8DU, 0x8EU, 0x8FU,
          0x90U, 0x91U, 0x92U, 0x93U, 0x94U, 0x95U, 0x96U, 0x97U, 0x98U, 0x99U, 0x9AU, 0x9BU, 0x9CU, 0x9DU, 0x9EU,
          0x9FU, 0xA0U, 0xA1U, 0xA2U, 0xA3U, 0xA4U, 0xA5U, 0xA6U, 0xA7U, 0xA8U, 0xA9U, 0xAAU, 0xABU, 0xACU, 0xADU,
          0xAEU, 0xAFU, 0xB0U, 0xB1U, 0xB2U, 0xB3U, 0xB4U, 0xB5U, 0xB6U, 0xB7U, 0xB8U, 0xB9U, 0xBAU, 0xBBU, 0xBCU,
          0xBDU, 0xBEU, 0xBFU }); // bulk arithmetic
  result.insert(result.end(), { 0xC6U, 0xCEU, 0xD6U, 0xDEU, 0xE6U, 0xEEU, 0xF6U, 0xFEU }); // immediate arithmetic
  return result;
}

auto ByteArithmeticDecoder::incDec(const OpcodeView& opcode) -> OperationUP
{
  auto function
      = opcode.lowerNibble() == 0x4U || opcode.lowerNibble() == 0xCU ? ByteAluFunction::Inc : ByteAluFunction::Dec;
  auto source = (opcode.lowerNibble() == 0x4U || opcode.lowerNibble() == 0x5U) && opcode.upperNibble() == 0x3U
      ? Source::Indirect
      : Source::Register;
  auto result = std::make_unique<ByteAluOperation>(function, source);
  switch (opcode.value()) {
  case 0x04U:
  case 0x05U:
    result->setRegister(ByteRegister::B);
    break;
  case 0x14U:
  case 0x15U:
    result->setRegister(ByteRegister::D);
    break;
  case 0x24U:
  case 0x25U:
    result->setRegister(ByteRegister::H);
    break;
  case 0x0CU:
  case 0x0DU:
    result->setRegister(ByteRegister::C);
    break;
  case 0x1CU:
  case 0x1DU:
    result->setRegister(ByteRegister::E);
    break;
  case 0x2CU:
  case 0x2DU:
    result->setRegister(ByteRegister::L);
    break;
  case 0x3CU:
  case 0x3DU:
    result->setRegister(ByteRegister::A);
    break;
  default:
    break;
  }
  return result;
}

auto ByteArithmeticDecoder::bulkArithmetic(const OpcodeView& opcode) -> OperationUP
{
  if ((opcode.lowerNibble() == 0x6U) || (opcode.lowerNibble() == 0xEU)) {
    return std::make_unique<ByteAluOperation>(bulkFunction(opcode), Source::Indirect);
  } else {
    auto op = std::make_unique<ByteAluOperation>(bulkFunction(opcode), Source::Register);
    op->setRegister(sourceRegister(opcode));
    return op;
  }
}

auto ByteArithmeticDecoder::immediate(const OpcodeView& opcode) -> OperationUP
{
  return std::make_unique<ByteAluOperation>(immediateFunction(opcode), Source::Immediate);
}

auto ByteArithmeticDecoder::sourceRegister(const OpcodeView& opcode) -> ByteRegister
{
  ByteRegister result = ByteRegister::None;
  switch (opcode.lowerNibble()) {
  case 0x0U:
  case 0x8U:
    result = ByteRegister::B;
    break;
  case 0x1U:
  case 0x9U:
    result = ByteRegister::C;
    break;
  case 0x2U:
  case 0xAU:
    result = ByteRegister::D;
    break;
  case 0x3U:
  case 0xBU:
    result = ByteRegister::E;
    break;
  case 0x4U:
  case 0xCU:
    result = ByteRegister::H;
    break;
  case 0x5U:
  case 0xDU:
    result = ByteRegister::L;
    break;
  case 0x7U:
  case 0xFU:
  default:
    result = ByteRegister::A;
    break;
  }
  return result;
}

auto ByteArithmeticDecoder::bulkFunction(const OpcodeView& opcode) -> ByteAluFunction
{
  if (opcode.lowerNibble() <= 0x7U) {
    switch (opcode.upperNibble()) {
    case 0x8U:
      return ByteAluFunction::Add;
      break;
    case 0x9U:
      return ByteAluFunction::Sub;
      break;
    case 0xAU:
      return ByteAluFunction::And;
      break;
    case 0xBU:
      return ByteAluFunction::Or;
      break;
    default:
      throw std::logic_error("Unimplemented");
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x8U:
      return ByteAluFunction::AddCarry;
      break;
    case 0x9U:
      return ByteAluFunction::SubCarry;
      break;
    case 0xAU:
      return ByteAluFunction::Xor;
      break;
    case 0xBU:
      return ByteAluFunction::Cp;
      break;
    default:
      throw std::logic_error("Unimplemented");
      break;
    }
  }
}

auto ByteArithmeticDecoder::immediateFunction(const OpcodeView& opcode) -> ByteAluFunction
{
  switch (opcode.value()) {
  case 0xC6U:
    return ByteAluFunction::Add;
    break;
  case 0xCEU:
    return ByteAluFunction::AddCarry;
    break;
  case 0xD6U:
    return ByteAluFunction::Sub;
    break;
  case 0xDEU:
    return ByteAluFunction::SubCarry;
    break;
  case 0xE6U:
    return ByteAluFunction::And;
    break;
  case 0xEEU:
    return ByteAluFunction::Xor;
    break;
  case 0xF6U:
    return ByteAluFunction::Or;
    break;
  case 0xFEU:
    return ByteAluFunction::Cp;
    break;
  default:
    throw std::logic_error { "Unimplemented opcode: " + std::to_string(opcode.value()) };
    break;
  }
}
