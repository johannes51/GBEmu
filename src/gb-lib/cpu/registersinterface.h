#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#include "cpu_defines.h"
#include "location/location_defines.h"

enum class ByteRegisters { A, B, C, D, E, H, L, None };

enum class WordRegisters { AF, BC, DE, HL, SP, PC, None };

class RegistersInterface {
public:
  RegistersInterface() = default;
  virtual ~RegistersInterface() = default;
  DISABLE_COPY_AND_MOVE(RegistersInterface)

  virtual Location<uint16_t> get(WordRegisters registerName) = 0;
  virtual Location<uint8_t> get(ByteRegisters registerName) = 0;

  virtual FlagsView& getFlags() = 0;
};

#endif // REGISTERS_H
