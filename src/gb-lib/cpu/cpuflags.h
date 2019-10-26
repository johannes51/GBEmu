#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "defines.h"
#include "flagsview.h"

class CpuFlags final : public FlagsView {
public:
  CpuFlags(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(CpuFlags)

  void setCarry();
  void clearCarry();
  bool carry();

private:
  uint8_t& buffer_;
  bool carry_;
};

#endif // CPUFLAGS_H
