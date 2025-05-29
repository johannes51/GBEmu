#ifndef MBC1_H
#define MBC1_H

#include "mbc.h"

#include <vector>

#include "mem/mem_defines.h"
#include "mem/rom/rombank.h"

enum class BankingMode {
  Rom,
  Ram,
};

class Mbc1 final : public Mbc {
public:
  explicit Mbc1(RomBankUP rom0, std::vector<RomBankUP>&& rom1Banks, IMemoryViewUP ram0);
  DISABLE_COPY_AND_MOVE(Mbc1)
  ~Mbc1() override = default;

  ILocation8& getLocation8(const address_type address) override;

  void handleWrite(const address_type address, const uint8_t value) override;

private:
  void updateSelectedRomBank();
  void updateSelectedRamBank();

  static constexpr address_type RamEnableTop = 0x1FFFU;
  static constexpr address_type RomBankNumberTop = Rom0Area.to;
  static constexpr address_type RamRomHBankNumberTop = 0x5FFFU;
  static constexpr address_type RomRamModeTop = Rom1Area.to;

  static constexpr uint8_t RamEnableMask = 0xAU;
  static constexpr uint8_t RomBankNumberMask = 0b11111U;
  static constexpr uint8_t RamRomHBankNumberMask = 0b11U;
  static constexpr uint8_t RomHBankShift = 5U;

  static const std::vector<MemoryArea> RomMemoryAreas;

  RomBankUP rom0_;
  std::vector<RomBankUP> rom1Banks_;
  IMemoryViewUP ram0_;

  std::vector<RomBankUP>::iterator selectedRomBank_;
  bool ramEnabled_;
  BankingMode bankingMode_;
  uint8_t romBankNumber_;
  uint8_t ramBankNumber_;
};

#endif // MBC1_H
