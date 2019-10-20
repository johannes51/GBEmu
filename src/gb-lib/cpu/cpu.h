#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"
#include "mem/mem_defines.h"


class Cpu
{
public:
  Cpu(RegistersInterfaceUP&& registers, const IMemoryViewSP& mem);

  void clock();

private:
  IMemoryViewSP mem_;
  RegistersInterfaceUP registers_;
};

#endif // CPU_H
