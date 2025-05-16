#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include "cpu_defines.h"
#include "mem/location16.h"
#include "mem/location8.h"

enum class ByteRegister { A = 0, F, B, C, D, E, H, L, NumRegs, None };

enum WordRegister { AF = 0, BC, DE, HL, SP, PC, NumRegs, None };

class RegistersInterface {
public:
  RegistersInterface() = default;
  virtual ~RegistersInterface() = default;
  DISABLE_COPY_AND_MOVE(RegistersInterface)

  virtual Location8 get(ByteRegister registerName) = 0;
  virtual Location16 get(WordRegister registerName) = 0;

  virtual FlagsView& getFlags() = 0;
  virtual const FlagsView& getFlags() const = 0;
};

#endif // REGISTERS_H
