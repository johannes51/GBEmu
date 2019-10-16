#ifndef CPU_DEFINES_H
#define CPU_DEFINES_H

#include <memory>

class Cpu;
using CpuUP = std::unique_ptr<Cpu>;

class Operation;

class RegistersInterface;
using RegistersInterfaceUP = std::unique_ptr<RegistersInterface>;

class FlagsView;

#endif // CPU_DEFINES_H
