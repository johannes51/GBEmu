#include "loadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/byteload.h"
#include "cpu/operation/wordload.h"
#include "opcodeview.h"

auto destination(const OpcodeView& opcode) -> std::pair<ByteLoad::Destination, ByteRegisters>
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
      throw std::logic_error("Unimplemented opcode: " + std::to_string(opcode.value()));
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
      break;
    default:
      throw std::logic_error("Unimplemented opcode: " + std::to_string(opcode.value()));
      break;
    }
  }
  return std::make_pair(dest, destRegister);
}

auto source(const OpcodeView& opcode) -> std::pair<ByteLoad::Source, ByteRegisters>
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
  default:
    throw std::logic_error("Unimplemented opcode: " + std::to_string(opcode.value()));
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
  }
  if (opSource.first == ByteLoad::Source::Register) {
    result->setSource(opSource.second);
  }
  return result;
}

auto loadImmediate(const OpcodeView opcode) -> OperationUP
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
  case 0x31: {
    auto p = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Immediate);
    p->setDestination(WordRegisters::SP);
    result = std::move(p);
    break;
  }
  case 0x3E: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::Immediate);
    p->setDestination(ByteRegisters::A);
    result = std::move(p);
    break;
  }
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
  return result;
}

auto loadImmediateIndirect(const OpcodeView opcode) -> OperationUP
{
  OperationUP result;
  switch (opcode.value()) {
  case 0xE0: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register, true);
    p->setSource(ByteRegisters::A);
    result = std::move(p);
    break;
  }
  case 0xEA: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::ImmediateIndirect);
    p->setDestination(ByteRegisters::A);
    result = std::move(p);
    break;
  }
  case 0xF0: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register, true);
    p->setSource(ByteRegisters::A);
    result = std::move(p);
    break;
  }
  case 0xFA: {
    auto p = std::make_unique<ByteLoad>(ByteLoad::Destination::Register, ByteLoad::Source::ImmediateIndirect);
    p->setDestination(ByteRegisters::A);
    result = std::move(p);
    break;
  }
  default:
    throw std::logic_error("Unimplemented");
    break;
  }
  return result;
}

auto loadRegisterIndirect(const OpcodeView opcode, bool store) -> OperationUP
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
  default:
    throw std::logic_error("Unimplemented opcode: " + std::to_string(opcode.value()));
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

auto LoadsDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  OpcodeView opc { opcodeLocation.get() };
  if (opc.value() >= 0x40 && opc.value() <= 0x7F) {
    return bulkLoad(opc);
  } if ((opc.lowerNibble() == 0x1 || opc.lowerNibble() == 0x6 || opc.lowerNibble() == 0xE)
      && (opc.upperNibble() <= 0x3)) {
    return loadImmediate(opc);
  } else if ((opc.lowerNibble() == 0x0 || opc.lowerNibble() == 0xA)
      && (opc.upperNibble() <= 0xE || opc.upperNibble() <= 0xF)) {
    return loadImmediateIndirect(opc);
  }
  throw std::logic_error("Unimplmented opcode: " + std::to_string(opc.value()));
}

auto LoadsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(),
      { 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51,
          0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63,
          0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
          /*0x76, HALT */ 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F }); // bulk loads
  result.insert(
      result.end(), { 0x01, 0x06, 0x0E, 0x11, 0x16, 0x1E, 0x21, 0x26, 0x2E, 0x31, 0x36, 0x3E }); // immediate loads
  result.insert(result.end(), { 0xE0, 0xEA, 0xF0, 0xFA }); // immediate indirect loads
  return result;
}
