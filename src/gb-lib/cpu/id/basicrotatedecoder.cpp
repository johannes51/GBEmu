#include "basicrotatedecoder.h"

#include "cpu/operation/basicrotate.h"
#include "opcodeview.h"

auto BasicRotateDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  const OpcodeView opcode { opcodeLocation.getByte() };
  return std::make_unique<BasicRotate>(
      (opcode.lowerNibble() == 0x7) ? RotateDirection::Left : RotateDirection::Right, opcode.upperNibble() == 0x0);
}

auto BasicRotateDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return { 0x07, 0x0F, 0x17, 0x1F }; }
