#include "serial.h"

#include "gbinterrupthandler.h"
#include "ops/shiftrotate.h"

Serial::Serial(IRegisterAdapter& sb, IRegisterAdapter& sc, IRegisterAdapter& rIf)
    : sb_(sb)
    , sc_(sc)
    , if_(rIf)
{
}

void Serial::clock()
{
  if (--remainingCpuTicks_ == 0U) {
    if (!sc_.testBit(TransferEnableBit)) {
      remainingSerialTicks_ = -1;
    } else {
      if (remainingSerialTicks_ < 0) {
        remainingSerialTicks_ = SerialBitCount;
      }
      if (sc_.testBit(ClockSelectBit)) {
        clockSerial();
      }
    }
    remainingCpuTicks_ = TickDivider;
  }
}

void Serial::clockSerial()
{
  if (remainingSerialTicks_ > 0) {
    --remainingSerialTicks_;
    clockRegister();
    if (remainingSerialTicks_ == 0) {
      sc_.setBit(TransferEnableBit, false);
      if_.setBit(SerialInterruptBit, true);
      remainingSerialTicks_ = -1;
    }
  }
}

void Serial::clockRegister()
{
  const auto newValue
      = static_cast<uint8_t>(static_cast<unsigned>(sb_.getByte() << 1U) | 1U); // shift in 1s, simulating no connection
  sb_.setByte(newValue);
}

void Serial::endTransfer() { }
