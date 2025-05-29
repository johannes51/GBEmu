#ifndef CPUFLAGS_H
#define CPUFLAGS_H

#include "defines.h"
#include "flagsview.h"
#include "mem/ilocation8.h"

class CpuFlags final : public FlagsView {
public:
  static constexpr auto ZERO_BIT = 7U;
  static constexpr auto SUBTRACT_BIT = 6U;
  static constexpr auto HALF_CARRY_BIT = 5U;
  static constexpr auto CARRY_BIT = 4U;

  CpuFlags(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(CpuFlags)

  void setZero() override;
  void clearZero() override;
  bool zero() const override;

  void setSubtract() override;
  void clearSubtract() override;
  bool subtract() const override;

  void setHalfCarry() override;
  void clearHalfCarry() override;
  bool halfCarry() const override;

  void setCarry() override;
  void clearCarry() override;
  bool carry() const override;

  void enableInterrupt() override;
  void disableInterrupt() override;
  bool interruptEnabled() const override;

  void halt() override;
  void unhalt() override;
  bool isHalt() const override;

private:
  uint8_t& buffer_;
  bool interrupt_;
  bool halt_;
};

#endif // CPUFLAGS_H
