#ifndef GBINTERRUPTHANDLER_H
#define GBINTERRUPTHANDLER_H

#include "interrupthandler.h"

#include <array>
#include <utility>

#include "io/iobank.h"
#include "io/ioregister.h"

constexpr uint8_t InterruptRegisterMask = 0b00011111U;

constexpr uint8_t VBlankInterruptBit = 0U;
constexpr uint8_t LcdInterruptBit = 1U;
constexpr uint8_t TimerInterruptBit = 2U;
constexpr uint8_t SerialInterruptBit = 3U;
constexpr uint8_t JoypadInterruptBit = 4U;
constexpr uint8_t NumInterrupts = 5U;

constexpr address_type VBlankInterruptAddress = 0x0040U;
constexpr address_type LcdInterruptAddress = 0x0048U;
constexpr address_type TimerInterruptAddress = 0x0050U;
constexpr address_type SerialInterruptAddress = 0x0058U;
constexpr address_type JoypadInterruptAddress = 0x0060U;

constexpr std::array<std::pair<uint8_t, address_type>, NumInterrupts> HandlerAdresses
    = { std::make_pair(VBlankInterruptBit, VBlankInterruptAddress),
        std::make_pair(LcdInterruptBit, LcdInterruptAddress), std::make_pair(TimerInterruptBit, TimerInterruptAddress),
        std::make_pair(SerialInterruptBit, SerialInterruptAddress),
        std::make_pair(JoypadInterruptBit, JoypadInterruptAddress) };

class GbInterruptHandler : public InterruptHandler {
public:
  explicit GbInterruptHandler(IoBank& io, ILocation8& ie);
  DISABLE_COPY_AND_MOVE(GbInterruptHandler)
  ~GbInterruptHandler() override = default;

  void execute(RegistersInterface& registers, IMemoryWordView& memory) override;

  bool isInterrupt() const override;

  IRegisterAdapter* getIf();

private:
  static constexpr address_type IfAddress = 0xFF0FU;

  IoRegister if_;
  ILocation8& ie_;

  std::pair<uint8_t, address_type> unmapInterrupt();
  static bool checkInterruptBit(const uint8_t& activeInterrupts, const uint8_t pos);
};

#endif // GBINTERRUPTHANDLER_H
