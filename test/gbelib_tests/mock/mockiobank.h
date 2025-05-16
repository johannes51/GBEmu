#ifndef MOCKIOBANK_H
#define MOCKIOBANK_H

#include "mem/registers/iobank.h"

#include "mockregisteradapter.h"

class MockIoBank : public IoBank {
public:
  MockIoBank(std::span<uint8_t, std::dynamic_extent> buffer)
      : IoBank({}, buffer)
      , buffer_(buffer)
  {
  }

  ByteLocationAdapterUP getRegisterLocation(const address_type address) override
  {
    (void)address;
    return std::make_unique<BufferLocation>(buffer_[0U]);
  }

private:
  std::span<uint8_t, std::dynamic_extent> buffer_;
};

#endif // MOCKIOBANK_H
