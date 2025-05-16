#include "wordloadsdecoder.h"

#include <stdexcept>

#include "cpu/operation/pushpop.h"
#include "cpu/operation/wordload.h"
#include "cpu/registersinterface.h"
#include "mem/location8.h"

auto WordLoadsDecoder::decode(const Location8& opcodeLocation) const -> OperationUP
{
  OperationUP result;
  const OpcodeView opcode { opcodeLocation.get() };
  if (opcode.value() == 0x08U) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xE8U) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate);
    resultWL->setDestination(WordRegister::SP);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xF8U) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate);
    resultWL->setDestination(WordRegister::HL);
    resultWL->setSource(WordRegister::SP);
    result = std::move(resultWL);
  } else if (opcode.value() == 0xF9U) {
    auto resultWL = std::make_unique<WordLoad>(WordLoad::Destination::Register, WordLoad::Source::Register);
    resultWL->setDestination(WordRegister::SP);
    resultWL->setSource(WordRegister::HL);
    result = std::move(resultWL);
  } else if (opcode.upperNibble() >= 0xCU) {
    result = std::make_unique<PushPop>(
        opcode.lowerNibble() == 0x1U ? PushPop::Direction::Pop : PushPop::Direction::Push, selectRegister(opcode));
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
  result.insert(result.end(), { 0x01U, 0x11U, 0x21U, 0x31U }); // immediate loads
  result.insert(result.end(), { 0x08U, 0xE8U, 0xF8U, 0xF9U }); // oddball loads
  result.insert(result.end(), { 0xC1U, 0xD1U, 0xE1U, 0xF1U, 0xC5U, 0xD5U, 0xE5U, 0xF5U }); // push/pop
  return result;
}

auto WordLoadsDecoder::selectRegister(const OpcodeView& opcode) -> WordRegister
{
  switch (opcode.upperNibble()) {
  case 0x0U:
  case 0xCU:
    return WordRegister::BC;
    break;
  case 0x1U:
  case 0xDU:
    return WordRegister::DE;
    break;
  case 0x2U:
  case 0xEU:
    return WordRegister::HL;
    break;
  case 0x3U:
    return WordRegister::SP;
    break;
  case 0xFU:
    return WordRegister::AF;
    break;
  default:
    throw std::invalid_argument("Unimplemented opcode: " + std::to_string(opcode.value()));
    break;
  }
}
