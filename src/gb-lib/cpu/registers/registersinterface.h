#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include <memory>

#include "flagsview.h"
#include "mem/ilocation16.h"
#include "mem/ilocation8.h"

enum class ByteRegister { A = 0, F, B, C, D, E, H, L, NumRegs, None };

enum WordRegister { AF = 0, BC, DE, HL, SP, PC, NumRegs, None };

class RegistersInterface {
public:
  RegistersInterface() = default;
  virtual ~RegistersInterface() = default;
  DISABLE_COPY_AND_MOVE(RegistersInterface)

  virtual ILocation8& get(ByteRegister registerName) = 0;
  virtual ILocation16& get(WordRegister registerName) = 0;

  virtual FlagsView& getFlags() = 0;
  virtual const FlagsView& getFlags() const = 0;
};

using RegistersInterfaceUP = std::unique_ptr<RegistersInterface>;

#endif // REGISTERS_H
