#ifndef ROMBANK_H
#define ROMBANK_H

#include "../common/bufferbank.h"

#include <memory>

#include "cart/mbc.h"
#include "romlocation.h"

class RomBank final : public BufferBank {
public:
  RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RomBank)
  ~RomBank() override = default;

  ILocation8& getLocation8(const address_type address) override;

  void setMbc(Mbc* value);

private:
  RomLocation loc_;
};

using RomBankUP = std::unique_ptr<RomBank>;

#endif // ROMBANK_H
