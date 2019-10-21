#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "flagsview.h"

#include <stdint.h>

class CpuFlags : public FlagsView {
public:
  CpuFlags(uint8_t &buffer);

  void setCarry();
  void clearCarry();
  bool carry();

private:
  uint8_t &buffer_;
  bool carry_;
};

#endif // CPUFLAGS_H
