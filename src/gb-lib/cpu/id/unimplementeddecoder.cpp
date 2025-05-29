#include "unimplementeddecoder.h"

#include <sstream>
#include <stdexcept>

#include "../operation/operation.h"

const std::vector<uint8_t> UnimplementedDecoder::decodedOpcodes_
    = { 0xD3U, 0xDBU, 0xDDU, 0xE3U, 0xE4U, 0xEBU, 0xECU, 0xEDU, 0xF4U, 0xFCU, 0xFDU };

auto UnimplementedDecoder::decode(const ILocation8& opcodeLocation) const -> OperationUP
{
  (void)opcodeLocation;
  std::stringstream stream;
  stream << "Unimplemented (in HW) opcode: " << std::hex << static_cast<int>(opcodeLocation.get());
  throw std::invalid_argument(stream.str());
  return {};
}

auto UnimplementedDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return decodedOpcodes_; }
