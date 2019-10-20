#ifndef CPU_DEFINES_H
#define CPU_DEFINES_H

#include <memory>

#include "defines.h"

class Cpu;
using CpuUP = std::unique_ptr<Cpu>;

class Operation;
using OperationUP = std::unique_ptr<Operation>;

class RegistersInterface;
using RegistersInterfaceUP = std::unique_ptr<RegistersInterface>;

class FlagsView;
using FlagsViewUP = std::unique_ptr<FlagsView>;

#endif // CPU_DEFINES_H
