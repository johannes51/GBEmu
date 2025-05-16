#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "id/instructiondecoder.h"
#include "mem/imemoryview.h"
#include "mem/location8.h"
#include "mem/registers/iregisteradapter.h"
#include "peripherals/interrupthandler.h"

class Cpu {
public:
  Cpu(IMemoryView& mem, RegistersInterfaceUP&& registers, IRegisterAdapterUP ie,
      InstructionDecoderUP instructionDecoder, InterruptHandlerUP interruptHandler);
  ~Cpu();
  DISABLE_COPY_AND_MOVE(Cpu)

  bool clock();

private:
  OperationUP loadNextOperation();
  Location8 fetchNextOpcode();

  IMemoryView& mem_;
  RegistersInterfaceUP registers_;
  IRegisterAdapterUP ie_;
  InstructionDecoderUP instructionDecoder_;
  InterruptHandlerUP interruptHandler_;
  bool executingInterrupt_ = false;

  OperationUP nextOperation_ = nullptr;
  unsigned ticksTillExecution_ = 0;
};

#endif // CPU_H
