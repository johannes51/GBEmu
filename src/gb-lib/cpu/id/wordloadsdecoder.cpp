#include "wordloadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/pushpop.h"
#include "cpu/operation/wordload.h"
#include "cpu/registersinterface.h"
#include "location/location.h"

auto WordLoadsDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  OperationUP result;
  const OpcodeView opcode { opcodeLocation.getByte() };
  if (opcode.value() == 0x08) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xE8) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate);
    resultWL->setDestination(WordRegister::SP);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xF8) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate);
    resultWL->setDestination(WordRegister::HL);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xF9) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Register);
    resultWL->setDestination(WordRegister::SP);
    resultWL->setSource(WordRegister::HL);
    result = std::move(resultWL);
  } else if (opcode.upperNibble() >= 0xC) {
    result = std::make_unique<PushPop>(
        opcode.lowerNibble() == 0x1 ? PushPop::Direction::Pop : PushPop::Direction::Push, selectRegister(opcode));
  } else {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Immediate);
    resultWL->setDestination(selectRegister(opcode));
    result = std::move(resultWL);
  }
  return result;
}

auto WordLoadsDecoder::decodedOpcodes() const -> std::vector<uint8_t>
{
  std::vector<uint8_t> result;
  result.insert(result.end(), { 0x01, 0x11, 0x21, 0x31 }); // immediate loads
  result.insert(result.end(), { 0x08, 0xE8, 0xF8, 0xF9 }); // oddball loads
  result.insert(result.end(), { 0xC1, 0xD1, 0xE1, 0xF1, 0xC5, 0xD5, 0xE5, 0xF5 }); // push/pop
  return result;
}

auto WordLoadsDecoder::selectRegister(const OpcodeView& opcode) -> WordRegister
{
  switch (opcode.upperNibble()) {
  case 0x0:
  case 0xC:
    return WordRegister::BC;
    break;
  case 0x1:
  case 0xD:
    return WordRegister::DE;
    break;
  case 0x2:
  case 0xE:
    return WordRegister::HL;
    break;
  case 0x3:
    return WordRegister::SP;
    break;
  case 0xF:
    return WordRegister::AF;
    break;
  default:
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
    break;
  }
}
