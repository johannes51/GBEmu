#ifndef DIVREGISTER_H
#define DIVREGISTER_H

#include "ioregister.h"

#include "defines.h"
#include "iobank.h"

constexpr uint16_t DivRegisterAddress = 0xFF04U;
constexpr uint16_t SystemTimerDivMask = 0b0000000000111111;

class DivRegister : public IoRegister {
public:
  explicit DivRegister();
  DISABLE_COPY_AND_MOVE(DivRegister)
  ~DivRegister() override = default;

  DivRegister& operator=(const uint8_t& rhs) override;

  void setByte(uint8_t value) override;
  void setBit(uint8_t pos, bool value) override;

  virtual bool testBitSystemTimer(uint8_t pos) const;

  virtual void clock();

private:
  uint16_t systemTimer_ = 0U;
};

#endif // DIVREGISTER_H
