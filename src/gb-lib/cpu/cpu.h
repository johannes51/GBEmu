#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "mem/mem_defines.h"

class Cpu {
public:
  Cpu(RegistersInterfaceUP &&registers, IMemoryViewSP mem);
  ~Cpu();
  DISABLE_COPY_AND_MOVE(Cpu)

  void clock();

private:
  IMemoryViewSP mem_;
  RegistersInterfaceUP registers_;
  OperationUP nextOperation_;
};

#endif // CPU_H
