#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "defines.h"
#include "flagsview.h"

class CpuFlags final : public FlagsView {
public:
  static constexpr auto ZERO_BIT = 7U;
  static constexpr auto CARRY_BIT = 4U;

  CpuFlags(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(CpuFlags)

  void setZero() override;
  void clearZero() override;
  bool zero() const override;

  void setCarry() override;
  void clearCarry() override;
  bool carry() const override;

  void enableInterrupt() override;
  void disableInterrupt() override;
  bool interruptEnabled() const override;

private:
  uint8_t& buffer_;
  bool interrupt_;

  void setBit(uint8_t pos);
  void clearBit(uint8_t pos);
  bool checkBit(uint8_t pos) const;
};

#endif // CPUFLAGS_H
