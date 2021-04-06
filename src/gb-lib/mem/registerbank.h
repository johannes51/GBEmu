#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include "imemorymanager.h"

class RegisterBank : public IMemoryManager {
public:
  RegisterBank(const address_type& start, const uint8_t& initial = 0x00);
  DISABLE_COPY_AND_MOVE(RegisterBank)

  std::vector<MemoryArea> availableAreas() override;

  Location<uint8_t> getByte(address_type address);
  Location<uint16_t> getWord(address_type address);

private:
  address_type start_;
  uint8_t buffer_;
};

#endif // REGISTERBANK_H
