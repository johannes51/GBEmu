#include "byteloadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/byteloadimmediate.h"
#include "cpu/operation/byteloadindirect.h"
#include "cpu/operation/byteloadoddball.h"
#include "cpu/operation/byteloadstandard.h"
#include "opcodeview.h"

auto destination(const OpcodeView& opcode) -> ByteRegister
{
  if (opcode.lowerNibble() < 0x8) {
    switch (opcode.upperNibble() % 0x4) {
    case 0x0:
      return ByteRegister::B;
      break;
    case 0x1:
      return ByteRegister::D;
      break;
    case 0x2:
      return ByteRegister::H;
      break;
    default:
      return ByteRegister::None;
      break;
    }
  } else {
    switch (opcode.upperNibble() % 0x4) {
    case 0x0:
      return ByteRegister::C;
      break;
    case 0x1:
      return ByteRegister::E;
      break;
    case 0x2:
      return ByteRegister::L;
      break;
    case 0x3:
      return ByteRegister::A;
      break;
    default:
      return ByteRegister::None;
      break;
    }
  }
}

auto bulkSource(const OpcodeView& opcode) -> ByteRegister
{
  switch (opcode.lowerNibble() % 0x8) {
  case 0x0:
    return ByteRegister::B;
    break;
  case 0x1:
    return ByteRegister::C;
    break;
  case 0x2:
    return ByteRegister::D;
    break;
  case 0x3:
    return ByteRegister::E;
    break;
  case 0x4:
    return ByteRegister::H;
    break;
  case 0x5:
    return ByteRegister::L;
    break;
  case 0x7:
    return ByteRegister::A;
    break;
  default:
    return ByteRegister::None;
    break;
  }
}

auto bulkLoad(const OpcodeView opcode) -> OperationUP
{
  return std::make_unique<ByteLoadStandard>(destination(opcode), bulkSource(opcode));
}

auto loadImmediate(const OpcodeView opcode) -> OperationUP
{
  const auto dest = destination(opcode);
  if (dest != ByteRegister::None) {
    return std::make_unique<ByteLoadImmediate>(dest);
  } else {
    return std::make_unique<ByteLoadImmediate>(WordRegister::HL);
  }
}

auto loadOddbal(const OpcodeView opcode) -> OperationUP
{
  const auto direction
      = (opcode.upperNibble() == 0xE) ? ByteLoadOddball::Direction::Indirect : ByteLoadOddball::Direction::Register;
  switch (opcode.lowerNibble()) {
  case 0x0:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::ImmediateZeroPage);
    break;
  case 0x2:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::RegisterC);
    break;
  case 0xA:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::ImmediateStandard);
    break;
  default:
    throw std::logic_error("Unreachable");
    break;
  }
}

auto loadRegisterIndirect(const OpcodeView opcode) -> OperationUP
{
  const auto direction = ((opcode.upperNibble() <= 0x3 && opcode.lowerNibble() == 0x2)
                             || (opcode.upperNibble() == 0x7 && opcode.lowerNibble() <= 0x7))
      ? ByteLoadIndirect::Direction::Indirect
      : ByteLoadIndirect::Direction::Register;

  const auto dirReg = (opcode.lowerNibble() <= 0x3) ? ByteRegister::A : destination(opcode);

  const auto indirReg = (opcode.upperNibble() >= 0x2)
      ? WordRegister::HL
      : (opcode.upperNibble() == 0x0 ? WordRegister::BC : WordRegister::DE);

  auto postAction = ByteLoadIndirect::Post::None;
  if (opcode.upperNibble() == 0x2) {
    postAction = ByteLoadIndirect::Post::Increment;
  } else if (opcode.upperNibble() == 0x1) {
    postAction = ByteLoadIndirect::Post::Decrement;
  }

  return std::make_unique<ByteLoadIndirect>(direction, dirReg, indirReg, postAction);
}

auto ByteLoadsDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opc { opcodeLocation.getByte() };

  if (opc.value() >= 0x40 && opc.value() <= 0x7F) {
    if (opc.lowerNibble() == 0x6 || opc.lowerNibble() == 0xE
        || (opc.upperNibble() == 0x7 && opc.lowerNibble() <= 0x7)) {
      return loadRegisterIndirect(opc);
    } else {
      return bulkLoad(opc);
    }
  } else if (opc.upperNibble() <= 0x3) {
    if (opc.lowerNibble() == 0x6 || opc.lowerNibble() == 0xE) {
      return loadImmediate(opc);
    } else if (opc.lowerNibble() == 0x2 || opc.lowerNibble() == 0xA) {
      return loadRegisterIndirect(opc);
    }
  } else if (opc.upperNibble() >= 0xE) {
    return loadOddbal(opc);
  }
  throw std::logic_error("Unimplmented opcode: " + std::to_string(opc.value()));
}

auto ByteLoadsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
          0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63,
          0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
          /*0x76, HALT */ 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F }); // bulk loads
  result.insert(result.end(), { 0x06, 0x0E, 0x16, 0x1E, 0x26, 0x2E, 0x3E }); // immediate loads
  result.insert(result.end(), { 0x02, 0x12, 0x22, 0x32, 0x0A, 0x1A, 0x2A, 0x3A, 0x36 }); // register indirect loads
  result.insert(result.end(), { 0xE0, 0xE2, 0xEA, 0xF0, 0xF2, 0xFA }); // oddball loads
  return result;
}
