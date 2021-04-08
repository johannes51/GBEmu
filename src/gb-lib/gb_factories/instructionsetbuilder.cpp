#include "instructionsetbuilder.h"

#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/bytearithmeticdecoder.h"
#include "cpu/id/byteloadsdecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/id/wordarithmeticdecoder.h"
#include "cpu/id/wordloadsdecoder.h"

auto InstructionSetBuilder::construct() -> InstructionDecoderUP
{
  auto result = std::make_unique<BaseInstructionDecoder>();

  result->registerDecoder(std::make_shared<ControlDecoder>());
  result->registerDecoder(std::make_shared<JumpsCallsDecoder>());
  result->registerDecoder(std::make_shared<ByteLoadsDecoder>());
  result->registerDecoder(std::make_shared<WordLoadsDecoder>());
  result->registerDecoder(std::make_shared<ByteArithmeticDecoder>());
  result->registerDecoder(std::make_shared<WordArithmeticDecoder>());

  return result;
}
