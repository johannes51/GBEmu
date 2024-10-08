#include "unimplementeddecoder.h"

#include <stdexcept>

#include "../operation/operation.h"

const std::vector<uint8_t> UnimplmentedDecoder::decodedOpcodes_
    = { 0xD3U, 0xDBU, 0xDDU, 0xE3U, 0xE4U, 0xEBU, 0xECU, 0xEDU, 0xF4U, 0xFCU, 0xFDU };

auto UnimplmentedDecoder::decode(const Location& opcodeLocation) const -> OperationUP
{
  (void)opcodeLocation;
  throw std::invalid_argument("Unimplemented (in HW) opcode");
  return {};
}

auto UnimplmentedDecoder::decodedOpcodes() const -> std::vector<uint8_t> { return decodedOpcodes_; }
