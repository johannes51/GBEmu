#ifndef SERIAL_H
#define SERIAL_H

#include "tickable.h"

#include "constants.h"
#include "mem/registers/iregisteradapter.h"

class Serial : public Tickable {
public:
  explicit Serial(IRegisterAdapter& sb, IRegisterAdapter& sc, IRegisterAdapter& rIf);
  DISABLE_COPY_AND_MOVE(Serial)
  ~Serial() override = default;

  void clock() override;

private:
  void clockSerial();
  void clockRegister();
  void endTransfer();

  static constexpr uint32_t SerialClock = 8192U;
  static constexpr uint16_t TickDivider = GB_CLOCK / SerialClock;
  static constexpr int8_t SerialBitCount = 8;

  static constexpr uint8_t ClockSelectBit = 0U;
  static constexpr uint8_t TransferEnableBit = 0U;

  IRegisterAdapter& sb_;
  IRegisterAdapter& sc_;
  IRegisterAdapter& if_;
  uint16_t remainingCpuTicks_ = TickDivider;
  int8_t remainingSerialTicks_ = -1;
};

#endif // SERIAL_H
