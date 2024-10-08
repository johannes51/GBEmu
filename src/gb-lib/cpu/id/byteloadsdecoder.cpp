#include "byteloadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/byteloadimmediate.h"
#include "cpu/operation/byteloadindirect.h"
#include "cpu/operation/byteloadoddball.h"
#include "cpu/operation/byteloadstandard.h"
#include "opcodeview.h"

auto destination(const OpcodeView& opcode) -> ByteRegister
{
  if (opcode.lowerNibble() < 0x8U) {
    switch (opcode.upperNibble() % 0x4U) {
    case 0x0U:
      return ByteRegister::B;
      break;
    case 0x1U:
      return ByteRegister::D;
      break;
    case 0x2U:
      return ByteRegister::H;
      break;
    default:
      return ByteRegister::None;
      break;
    }
  } else {
    switch (opcode.upperNibble() % 0x4U) {
    case 0x0U:
      return ByteRegister::C;
      break;
    case 0x1U:
      return ByteRegister::E;
      break;
    case 0x2U:
      return ByteRegister::L;
      break;
    case 0x3U:
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
  switch (opcode.lowerNibble() % 0x8U) {
  case 0x0U:
    return ByteRegister::B;
    break;
  case 0x1U:
    return ByteRegister::C;
    break;
  case 0x2U:
    return ByteRegister::D;
    break;
  case 0x3U:
    return ByteRegister::E;
    break;
  case 0x4U:
    return ByteRegister::H;
    break;
  case 0x5U:
    return ByteRegister::L;
    break;
  case 0x7U:
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
      = (opcode.upperNibble() == 0xEU) ? ByteLoadOddball::Direction::Indirect : ByteLoadOddball::Direction::Register;
  switch (opcode.lowerNibble()) {
  case 0x0U:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::ImmediateZeroPage);
    break;
  case 0x2U:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::RegisterC);
    break;
  case 0xAU:
    return std::make_unique<ByteLoadOddball>(direction, ByteLoadOddball::Indirection::ImmediateStandard);
    break;
  default:
    throw std::logic_error("Unreachable");
    break;
  }
}

auto loadRegisterIndirect(const OpcodeView opcode) -> OperationUP
{
  const auto direction = ((opcode.upperNibble() <= 0x3U && opcode.lowerNibble() == 0x2U)
                             || (opcode.upperNibble() == 0x7U && opcode.lowerNibble() <= 0x7U))
      ? ByteLoadIndirect::Direction::Indirect
      : ByteLoadIndirect::Direction::Register;

  const auto dirReg = (opcode.lowerNibble() <= 0x3U) ? ByteRegister::A : destination(opcode);

  auto indirReg = WordRegister::None;
  if (opcode.upperNibble() >= 0x2U) {
    indirReg = WordRegister::HL;
  } else if (opcode.upperNibble() == 0x0U) {
    indirReg = WordRegister::BC;
  } else {
    indirReg = WordRegister::DE;
  }
  auto postAction = ByteLoadIndirect::Post::None;
  if (opcode.upperNibble() == 0x2U) {
    postAction = ByteLoadIndirect::Post::Increment;
  } else if (opcode.upperNibble() == 0x1U) {
    postAction = ByteLoadIndirect::Post::Decrement;
  }

  return std::make_unique<ByteLoadIndirect>(direction, dirReg, indirReg, postAction);
}

auto ByteLoadsDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opc { opcodeLocation.getByte() };

  if (opc.value() >= 0x40U && opc.value() <= 0x7FU) {
    if (opc.lowerNibble() == 0x6U || opc.lowerNibble() == 0xEU
        || (opc.upperNibble() == 0x7U && opc.lowerNibble() <= 0x7U)) {
      return loadRegisterIndirect(opc);
    } else {
      return bulkLoad(opc);
    }
  } else if (opc.upperNibble() <= 0x3U) {
    if (opc.lowerNibble() == 0x6U || opc.lowerNibble() == 0xEU) {
      return loadImmediate(opc);
    } else if (opc.lowerNibble() == 0x2U || opc.lowerNibble() == 0xAU) {
      return loadRegisterIndirect(opc);
    }
  } else if (opc.upperNibble() >= 0xEU) {
    return loadOddbal(opc);
  }
  throw std::logic_error("Unimplmented opcode: " + std::to_string(opc.value()));
}

auto ByteLoadsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      { 0x40U, 0x41U, 0x42U, 0x43U, 0x44U, 0x45U, 0x46U, 0x47U, 0x48U, 0x49U, 0x4AU, 0x4BU, 0x4CU, 0x4DU, 0x4EU, 0x4FU,
          0x50U, 0x51U, 0x52U, 0x53U, 0x54U, 0x55U, 0x56U, 0x57U, 0x58U, 0x59U, 0x5AU, 0x5BU, 0x5CU, 0x5DU, 0x5EU,
          0x5FU, 0x60U, 0x61U, 0x62U, 0x63U, 0x64U, 0x65U, 0x66U, 0x67U, 0x68U, 0x69U, 0x6AU, 0x6BU, 0x6CU, 0x6DU,
          0x6EU, 0x6FU, 0x70U, 0x71U, 0x72U, 0x73U, 0x74U, 0x75U,
          /*0x76U, HALT */ 0x77U, 0x78U, 0x79U, 0x7AU, 0x7BU, 0x7CU, 0x7DU, 0x7EU, 0x7FU }); // bulk loads
  result.insert(result.end(), { 0x06U, 0x0EU, 0x16U, 0x1EU, 0x26U, 0x2EU, 0x3EU }); // immediate loads
  result.insert(
      result.end(), { 0x02U, 0x12U, 0x22U, 0x32U, 0x0AU, 0x1AU, 0x2AU, 0x3AU, 0x36U }); // register indirect loads
  result.insert(result.end(), { 0xE0U, 0xE2U, 0xEAU, 0xF0U, 0xF2U, 0xFAU }); // oddball loads
  return result;
}
