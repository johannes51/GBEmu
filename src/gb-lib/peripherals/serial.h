#ifndef SERIAL_H
#define SERIAL_H

#include "tickable.h"

#include "constants.h"
#include "io/fixedmaskioregister.h"
#include "io/iobank.h"
#include "io/ioregister.h"
#include "io/iregisteradapter.h"

class Serial : public Tickable {
public:
  explicit Serial(IoBank& io, IRegisterAdapter& rIf);
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

  IoRegister sb_;
  FixedMaskIoRegister<0b01111110U> sc_;
  IRegisterAdapter& if_;
  uint16_t remainingCpuTicks_ = TickDivider;
  int8_t remainingSerialTicks_ = -1;
};

#endif // SERIAL_H
