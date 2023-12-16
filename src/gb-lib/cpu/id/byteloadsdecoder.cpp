#include "byteloadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/byteload.h"
#include "opcodeview.h"

auto destination(const OpcodeView& opcode) -> std::pair<ByteLoad::Destination, ByteRegister>
{
  auto destRegister = ByteRegister::A;
  auto dest = ByteLoad::Destination::Register;
  if (opcode.lowerNibble() <= 0x7) {
    switch (opcode.upperNibble()) {
    case 0x4:
      destRegister = ByteRegister::B;
      break;
    case 0x5:
      destRegister = ByteRegister::D;
      break;
    case 0x6:
      destRegister = ByteRegister::H;
      break;
    case 0x7:
      dest = ByteLoad::Destination::RegisterIndirect;
      break;
    default:
      throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
      break;
    }
  } else {
    switch (opcode.upperNibble()) {
    case 0x4:
      destRegister = ByteRegister::C;
      break;
    case 0x5:
      destRegister = ByteRegister::E;
      break;
    case 0x6:
      destRegister = ByteRegister::L;
      break;
    case 0x7:
      destRegister = ByteRegister::A;
      break;
    default:
      throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
      break;
    }
  }
  return std::make_pair(dest, destRegister);
}

auto source(const OpcodeView& opcode) -> std::pair<ByteLoad::Source, ByteRegister>
{
  auto srcRegister = ByteRegister::A;
  auto src = ByteLoad::Source::Register;
  switch (opcode.lowerNibble()) {
  case 0x0:
  case 0x8:
    srcRegister = ByteRegister::B;
    break;
  case 0x1:
  case 0x9:
    srcRegister = ByteRegister::C;
    break;
  case 0x2:
  case 0xA:
    srcRegister = ByteRegister::D;
    break;
  case 0x3:
  case 0xB:
    srcRegister = ByteRegister::E;
    break;
  case 0x4:
  case 0xC:
    srcRegister = ByteRegister::H;
    break;
  case 0x5:
  case 0xD:
    srcRegister = ByteRegister::L;
    break;
  case 0x6:
  case 0xE:
    src = ByteLoad::Source::RegisterIndirect;
    break;
  case 0x7:
  case 0xF:
    srcRegister = ByteRegister::A;
    break;
  default:
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
    break;
  }
  return std::make_pair(src, srcRegister);
}

auto bulkLoad(const OpcodeView opcode) -> OperationUP
{
  if (opcode.value() == 0x76) {
    throw std::logic_error("HALT unimplemented");
  }
  const auto opDestination = destination(opcode);
  const auto opSource = source(opcode);
  auto result = std::make_unique<ByteLoad>(opDestination.first, opSource.first);
  if (opDestination.first == ByteLoad::Destination::Register) {
    result->setDestination(opDestination.second);
  } else if (opDestination.first == ByteLoad::Destination::RegisterIndirect) {
    result->setDestination(WordRegister::HL);
  }
  if (opSource.first == ByteLoad::Source::Register) {
    result->setSource(opSource.second);
  } else if (opSource.first == ByteLoad::Source::RegisterIndirect) {
    result->setSource(WordRegister::HL);
  }
  return result;
}

auto loadImmediate(const OpcodeView opcode) -> OperationUP
{
  ByteRegister reg = ByteRegister::None;
  switch (opcode.value()) {
  case 0x06:
    reg = ByteRegister::B;
    break;
  case 0x0E:
    reg = ByteRegister::C;
    break;
  case 0x16:
    reg = ByteRegister::D;
    break;
  case 0x1E:
    reg = ByteRegister::E;
    break;
  case 0x26:
    reg = ByteRegister::H;
    break;
  case 0x2E:
    reg = ByteRegister::L;
    break;
  case 0x3E:
    reg = ByteRegister::A;
    break;
  default:
    break;
  }
  if (reg != ByteRegister::None) {
    auto result = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::Immediate);
    result->setDestination(reg);
    return result;
  } else {
    auto result = std::make_unique<ByteLoad>(ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Immediate);
    result->setDestination(WordRegister::HL);
    return result;
  }
}

auto loadImmediateIndirect(const OpcodeView opcode) -> OperationUP
{
  OperationUP result;
  switch (opcode.value()) {
  case 0x02: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register);
    p->setDestination(WordRegister::BC);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0x12: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register);
    p->setDestination(WordRegister::DE);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0x22: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register);
    p->setDestination(WordRegister::HL);
    p->setPostAction(ByteLoad::Post::Increment);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0x32: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register);
    p->setDestination(WordRegister::HL);
    p->setPostAction(ByteLoad::Post::Decrement);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0x0A: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect);
    p->setDestination(ByteRegister::A);
    p->setSource(WordRegister::BC);
    result = std::move(p);
    break;
  }
  case 0x1A: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect);
    p->setDestination(ByteRegister::A);
    p->setSource(WordRegister::DE);
    result = std::move(p);
    break;
  }
  case 0x2A: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect);
    p->setDestination(ByteRegister::A);
    p->setSource(WordRegister::HL);
    p->setPostAction(ByteLoad::Post::Increment);
    result = std::move(p);
    break;
  }
  case 0x3A: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect);
    p->setDestination(ByteRegister::A);
    p->setSource(WordRegister::HL);
    p->setPostAction(ByteLoad::Post::Decrement);
    result = std::move(p);
    break;
  }
  case 0xE0: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register, true);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0xEA: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::ImmediateIndirect);
    p->setDestination(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0xF0: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register, true);
    p->setSource(ByteRegister::A);
    result = std::move(p);
    break;
  }
  case 0xFA: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::ImmediateIndirect);
    p->setDestination(ByteRegister::A);
    result = std::move(p);
    break;
  }
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
  return result;
}

auto loadRegisterIndirect(const OpcodeView opcode) -> OperationUP
{
  auto store = opcode.lowerNibble() == 0x2;
  auto dest = store ? ByteLoad::Destination::RegisterIndirect : ByteLoad::Destination::Register;
  auto src = store ? ByteLoad::Source::Register : ByteLoad::Source::RegisterIndirect;
  auto result = std::make_unique<ByteLoad>(dest, src);
  WordRegister indirectRegister = WordRegister::HL;
  switch (opcode.upperNibble()) {
  case 0x0:
    indirectRegister = WordRegister::BC;
    break;
  case 0x1:
    indirectRegister = WordRegister::DE;
    break;
  case 0x2:
    indirectRegister = WordRegister::HL;
    result->setPostAction(ByteLoad::Post::Increment);
    break;
  case 0x3:
    indirectRegister = WordRegister::HL;
    result->setPostAction(ByteLoad::Post::Decrement);
    break;
  default:
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
    break;
  }
  if (store) {
    result->setDestination(indirectRegister);
    result->setSource(ByteRegister::A);
  } else {
    result->setDestination(ByteRegister::A);
    result->setSource(indirectRegister);
  }
  return result;
}

auto ByteLoadsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  const OpcodeView opc { opcodeLocation.get() };

  if (opc.value() >= 0x40 && opc.value() <= 0x7F) {
    return bulkLoad(opc);
  } else if (opc.upperNibble() <= 0x3) {
    if (opc.lowerNibble() == 0x6 || opc.lowerNibble() == 0xE) {
      return loadImmediate(opc);
    } else if (opc.lowerNibble() == 0x2 || opc.lowerNibble() == 0xA) {
      return loadRegisterIndirect(opc);
    }
  } else if (opc.upperNibble() >= 0xE) {
    return loadImmediateIndirect(opc);
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
