#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include "cpu_defines.h"
#include "location/location_defines.h"

enum class ByteRegister { A, B, C, D, E, H, L, None };

enum class WordRegister { AF, BC, DE, HL, SP, PC, None };

class RegistersInterface {
public:
  RegistersInterface() = default;
  virtual ~RegistersInterface() = default;
  DISABLE_COPY_AND_MOVE(RegistersInterface)

  virtual Location<uint8_t> get(ByteRegister registerName) = 0;
  virtual Location<uint16_t> get(WordRegister registerName) = 0;

  virtual FlagsView& getFlags() = 0;
  virtual const FlagsView& getFlags() const = 0;
};

#endif // REGISTERS_H
