#ifndef SINGLEREGISTERBANK_H
#define SINGLEREGISTERBANK_H

#include "../common/bufferbank.h"

#include "../registers/iregisteradapter.h"

class SingleRegisterBank final : public BufferBank {
public:
  SingleRegisterBank(const address_type& start, const uint8_t& initial = 0x00);
  DISABLE_COPY_AND_MOVE(SingleRegisterBank)

  Location8 getLocation8(const address_type address) override;
  Location16 getLocation16(const address_type address) override;

  std::vector<MemoryArea> availableAreas() override;

  IRegisterAdapterUP asRegister();

  uint8_t& buffer() { return value_; }
  const uint8_t& buffer() const { return value_; }

private:
  address_type start_;
  uint8_t value_;
};

#endif // SINGLEREGISTERBANK_H
