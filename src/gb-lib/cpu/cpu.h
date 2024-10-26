#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "operation/operation.h"

class Cpu {
public:
  Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem, InstructionDecoderUP instructionDecoder);
  ~Cpu();
  DISABLE_COPY_AND_MOVE(Cpu)

  void clock();

private:
  LocationUP nextOpcode();

  const IMemoryViewSP mem_;
  const RegistersInterfaceUP registers_;
  const InstructionDecoderUP instructionDecoder_;

  OperationUP nextOperation_ = nullptr;
  unsigned ticksTillExecution_ = 0;
};

#endif // CPU_H
