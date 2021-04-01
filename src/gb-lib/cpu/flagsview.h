#ifndef FLAGSVIEW_H
#define FLAGSVIEW_H

#include <memory>

class FlagsView {
public:
  virtual ~FlagsView() = default;

  virtual void setCarry() = 0;
  virtual void clearCarry() = 0;
  virtual bool carry() const = 0;

  virtual void setZero() = 0;
  virtual void clearZero() = 0;
  virtual bool zero() const = 0;

  virtual void enableInterrupt() = 0;
  virtual void disableInterrupt() = 0;
  virtual bool interruptEnabled() const = 0;

protected:
  FlagsView() = default;
};

using FlagsViewUP = std::unique_ptr<FlagsView>;

#endif // FLAGSVIEW_H
