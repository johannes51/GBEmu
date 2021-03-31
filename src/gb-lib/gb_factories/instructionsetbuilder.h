#ifndef INSTRUCTIONSETBUILDER_H
#define INSTRUCTIONSETBUILDER_H

#include "cpu/id/instructiondecoder.h"

class InstructionSetBuilder {
public:
  InstructionSetBuilder() = delete;

  static InstructionDecoderUP construct();
};

#endif // INSTRUCTIONSETBUILDER_H
