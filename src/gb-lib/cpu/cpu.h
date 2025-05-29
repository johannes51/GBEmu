#ifndef CPU_H
#define CPU_H

#include "id/instructiondecoder.h"
#include "io/ioregister.h"
#include "mem/ilocation8.h"
#include "mem/imemoryview.h"
#include "peripherals/interrupthandler.h"
#include "registers/registersinterface.h"

class Cpu {
public:
  Cpu(IMemoryWordView& mem, RegistersInterfaceUP registers, InstructionDecoderUP instructionDecoder,
      InterruptHandlerUP interruptHandler);
  ~Cpu() = default;
  DISABLE_COPY_AND_MOVE(Cpu)

  bool clock();

private:
  OperationUP loadNextOperation();
  ILocation8& fetchNextOpcode();

  IMemoryWordView& mem_;
  RegistersInterfaceUP registers_;
  InstructionDecoderUP instructionDecoder_;
  InterruptHandlerUP interruptHandler_;
  bool executingInterrupt_ = false;

  OperationUP nextOperation_;
  unsigned ticksTillExecution_ = 0;
};

#endif // CPU_H
