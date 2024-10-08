#ifndef REGISTERBANK_H
#define REGISTERBANK_H

#include "bufferbank.h"

class RegisterBank final : public BufferBank {
public:
  RegisterBank(const address_type& start, const uint8_t& initial = 0x00);
  DISABLE_COPY_AND_MOVE(RegisterBank)

  LocationUP getLocation(const address_type address, bool tryWord = false) override;

  std::vector<MemoryArea> availableAreas() override;

  uint8_t& buffer() { return value_; }
  const uint8_t& buffer() const { return value_; }

private:
  address_type start_;
  uint8_t value_;
};

#endif // REGISTERBANK_H
