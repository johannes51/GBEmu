#ifndef GBINTERRUPTHANDLER_H
#define GBINTERRUPTHANDLER_H

#include "interrupthandler.h"

#include <array>
#include <utility>

#include "mem/registers/iregisteradapter.h"

constexpr uint8_t InterruptRegisterMask = 0b00011111U;

class GbInterruptHandler : public InterruptHandler {
public:
  GbInterruptHandler(IRegisterAdapterSP rIf, IRegisterAdapterSP rIe);
  ~GbInterruptHandler() override = default;

  void execute(RegistersInterface& registers, IMemoryView& memory) override;

  bool isInterrupt() const override;

private:
  IRegisterAdapterSP if_;
  IRegisterAdapterSP ie_;

  static constexpr uint8_t NumInterrupts = 5U;
  static constexpr std::array<uint8_t, NumInterrupts> HandlerAdresses = { 0x0040U, 0x0048U, 0x0050U, 0x0058U, 0x0060U };

  std::pair<uint8_t, address_type> unmapInterrupt();
  static bool checkInterruptBit(const uint8_t& activeInterrupts, const uint8_t pos);
};

#endif // GBINTERRUPTHANDLER_H
