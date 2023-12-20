#include "unimplementeddecoder.h"

#include <stdexcept>

#include "../operation/operation.h"

const std::vector<uint8_t> UnimplmentedDecoder::decodedOpcodes_
    = { 0xD3, 0xDB, 0xDD, 0xE3, 0xE4, 0xEB, 0xEC, 0xED, 0xF4, 0xFC, 0xFD };

auto UnimplmentedDecoder::decode(const Location<uint8_t>& opcodeLocation) -> OperationUP
{
  (void)opcodeLocation;
  throw std::invalid_argument("Unimplemented (in HW) opcode");
  return {};
}

std::vector<uint8_t> UnimplmentedDecoder::decodedOpcodes() const { return decodedOpcodes_; }
