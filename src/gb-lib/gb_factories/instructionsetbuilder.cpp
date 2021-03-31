#include "instructionsetbuilder.h"

#include "cpu/id/arithmeticdecoder.h"
#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/id/loadsdecoder.h"

auto InstructionSetBuilder::construct() -> InstructionDecoderUP
{
  auto result = std::make_unique<BaseInstructionDecoder>();

  auto ctrl = std::make_shared<ControlDecoder>();
  auto jp_cl = std::make_shared<JumpsCallsDecoder>();
  auto ld = std::make_shared<LoadsDecoder>();
  auto arit = std::make_shared<ArithmeticDecoder>();

  result->registerDecoder(ctrl);
  result->registerDecoder(jp_cl);
  result->registerDecoder(ld);
  result->registerDecoder(arit);
  return result;
}