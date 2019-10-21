#ifndef ROMBANK_H
#define ROMBANK_H

#include "singleareamanager.h"

class RomBank final : public SingleAreaManager {
public:
  RomBank(MemoryArea area, std::vector<uint8_t> &&buffer);

  LocationUP<uint8_t> getByte(address_type address) override;
  LocationUP<uint16_t> getWord(address_type address) override;

private:
  std::vector<uint8_t> buffer_;
};

#endif // ROMBANK_H
