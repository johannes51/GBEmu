#ifndef REGISTERBUFFER_H
#define REGISTERBUFFER_H

#include "iregisteradapter.h"

class RegisterBuffer : public IRegisterAdapter {
public:
  explicit RegisterBuffer(uint8_t initial = 0U);
  DISABLE_COPY_AND_MOVE(RegisterBuffer)

  uint8_t get() const override;
  void set(uint8_t value) override;

  bool testBit(uint8_t pos) const override;
  void setBit(uint8_t pos, bool value) override;

private:
  uint8_t value_;
};

#endif // REGISTERBUFFER_H
