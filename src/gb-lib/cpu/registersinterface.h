#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include "cpu_defines.h"
#include "location/register16.h"
#include "location/register8.h"

enum class ByteRegister { A = 0, F, B, C, D, E, H, L, NumRegs, None };

enum WordRegister { AF = 0, BC, DE, HL, SP, PC, NumRegs, None };

class RegistersInterface {
public:
  RegistersInterface() = default;
  virtual ~RegistersInterface() = default;
  DISABLE_COPY_AND_MOVE(RegistersInterface)

  virtual Register8UP get(ByteRegister registerName) = 0;
  virtual Register16UP get(WordRegister registerName) = 0;

  virtual FlagsView& getFlags() = 0;
  virtual const FlagsView& getFlags() const = 0;
};

#endif // REGISTERS_H
