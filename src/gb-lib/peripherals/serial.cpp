#include "serial.h"

#include "gbinterrupthandler.h"
#include "ops/shiftrotate.h"

constexpr address_type SbAddress = 0xFF01U;
constexpr address_type ScAddress = 0xFF02U;
constexpr uint8_t ScInitial = 0x7EU;

Serial::Serial(IoBank& io, IRegisterAdapter& rIf)
    : sb_()
    , sc_(ScInitial)
    , if_(rIf)
{
  io.registerRegister(SbAddress, &sb_);
  io.registerRegister(ScAddress, &sc_);
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
