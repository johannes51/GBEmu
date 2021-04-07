#include "instructionsetbuilder.h"

#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/bytearithmeticdecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/id/loadsdecoder.h"
#include "cpu/id/stackopdecoder.h"
#include "cpu/id/wordarithmeticdecoder.h"


auto InstructionSetBuilder::construct() -> InstructionDecoderUP
{
  auto result = std::make_unique<BaseInstructionDecoder>();

  auto ctrl = std::make_shared<ControlDecoder>();
  auto jp_cl = std::make_shared<JumpsCallsDecoder>();
  auto ld = std::make_shared<LoadsDecoder>();
  auto arit8 = std::make_shared<ByteArithmeticDecoder>();
  auto arit16 = std::make_shared<WordArithmeticDecoder>();
  auto stack = std::make_shared<StackOpDecoder>();

  result->registerDecoder(ctrl);
  result->registerDecoder(jp_cl);
  result->registerDecoder(ld);
  result->registerDecoder(arit8);
  result->registerDecoder(arit16);
  result->registerDecoder(stack);
  return result;
}
