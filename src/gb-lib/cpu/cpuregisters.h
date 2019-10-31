#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include <unordered_map>

#include "location/location_defines.h"
#include "registersinterface.h"

class CpuRegisters final : public RegistersInterface {
public:
  CpuRegisters();
  ~CpuRegisters();
  DISABLE_COPY_AND_MOVE(CpuRegisters)

  Location<uint16_t> get(WordRegisters registerName) override;
  Location<uint8_t> get(ByteRegisters registerName) override;
  FlagsView& getFlags() override;

private:
  enum class RegisterName { A, F, B, C, D, E, H, L, SPu, SPl, PCu, PCl };

  std::unordered_map<RegisterName, uint8_t> registers_;
  const FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
