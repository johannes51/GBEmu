#ifndef DIVREGISTER_H
#define DIVREGISTER_H

#include "memoryregisteradapter.h"

#include "defines.h"

constexpr uint16_t DivRegisterAdress = 0xFF04U;
constexpr uint16_t SystemTimerDivMask = 0b0000000000111111;

class DivRegister : public MemoryRegisterAdapter {
public:
  explicit DivRegister(IMemoryViewSP mem);
  DISABLE_COPY_AND_MOVE(DivRegister)
  ~DivRegister() override = default;

  void set(uint8_t value) override;
  void setBit(uint8_t pos, bool value) override;
  virtual bool testBitSystemTimer(uint8_t pos) const;

  virtual void clock();

private:
  uint16_t systemTimer_ = 0U;

  void updateDiv();
};

using DivRegisterSP = std::shared_ptr<DivRegister>;

#endif // DIVREGISTER_H
