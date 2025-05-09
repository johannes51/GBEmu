#ifndef MOCKFLAGS_H
#define MOCKFLAGS_H

#include "cpu/flagsview.h"

class MockFlags : public FlagsView {
public:
  void setZero() override { }
  void clearZero() override { }
  bool zero() const override { return false; }
  void setHalfCarry() override { }
  void clearHalfCarry() override { }
  bool halfCarry() const override { return false; }
  void setSubtract() override { }
  void clearSubtract() override { }
  bool subtract() const override { return false; }
  void setCarry() override { }
  void clearCarry() override { }
  bool carry() const override { return false; }
  void enableInterrupt() override { }
  void disableInterrupt() override { }
  bool interruptEnabled() const override { return false; }
};

#endif // MOCKFLAGS_H
