#ifndef FLAGSVIEW_H
#define FLAGSVIEW_H

#include <memory>

class FlagsView {
public:
  virtual ~FlagsView() = default;

  virtual void setCarry() = 0;
  virtual void clearCarry() = 0;
  virtual bool carry() = 0;

protected:
  FlagsView();
};

using FlagsViewUP = std::unique_ptr<FlagsView>;

#endif // FLAGSVIEW_H
