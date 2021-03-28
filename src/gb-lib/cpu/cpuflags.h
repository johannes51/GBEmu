#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "defines.h"
#include "flagsview.h"

class CpuFlags final : public FlagsView {
public:
  CpuFlags(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(CpuFlags)

  void setCarry() override;
  void clearCarry() override;
  bool carry() override;

  void enableInterrupt() override;
  void disableInterrupt() override;
  bool interruptEnabled() override;

private:
  uint8_t& buffer_;
  bool carry_;
  bool interrupt_;
};

#endif // CPUFLAGS_H
