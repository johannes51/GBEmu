#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include <vector>

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
  std::vector<uint8_t> registers_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
