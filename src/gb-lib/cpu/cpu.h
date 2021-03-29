#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "location/location_defines.h"
#include "mem/mem_defines.h"

class Cpu {
public:
  Cpu(RegistersInterfaceUP&& registers, IMemoryViewSP mem);
  ~Cpu();
  DISABLE_COPY_AND_MOVE(Cpu)

  void clock();

private:
  Location<uint8_t> nextOpcode();

  const IMemoryViewSP mem_;
  const RegistersInterfaceUP registers_;
  OperationUP nextOperation_;
  unsigned int ticksTillExecution_ = 0;
};

#endif // CPU_H
