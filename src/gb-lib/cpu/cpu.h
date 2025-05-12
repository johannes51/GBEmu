#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "location/location8.h"
#include "mem/imemoryview.h"
#include "peripherals/interrupthandler.h"

class Cpu {
public:
  Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem, InstructionDecoderUP instructionDecoder,
      InterruptHandlerUP interruptHandler);
  ~Cpu();
  DISABLE_COPY_AND_MOVE(Cpu)

  bool clock();

private:
  OperationUP loadNextOperation();
  Location8UP fetchNextOpcode();

  const IMemoryViewSP mem_;
  const RegistersInterfaceUP registers_;
  const InstructionDecoderUP instructionDecoder_;
  InterruptHandlerUP interruptHandler_;
  bool executingInterrupt_ = false;

  OperationUP nextOperation_ = nullptr;
  unsigned ticksTillExecution_ = 0;
};

#endif // CPU_H
