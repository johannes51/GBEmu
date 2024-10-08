#include "basicrotatedecoder.h"

#include "cpu/operation/basicrotate.h"
#include "opcodeview.h"

auto BasicRotateDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };
  return std::make_unique<BasicRotate>(
      (opcode.lowerNibble() == 0x7U) ? RotateDirection::Left : RotateDirection::Right, opcode.upperNibble() == 0x0U);
}

auto BasicRotateDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return { 0x07U, 0x0FU, 0x17U, 0x1FU }; }
