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

  Location<uint8_t> get(ByteRegister registerName) override;
  Location<uint16_t> get(WordRegister registerName) override;

  FlagsView& getFlags() override;
  const FlagsView& getFlags() const override;

private:
  enum class RegisterName { A, F, B, C, D, E, H, L, SPu, SPl, PCu, PCl };

  std::unordered_map<RegisterName, uint8_t> registers_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
