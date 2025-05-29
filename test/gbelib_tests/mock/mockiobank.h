#ifndef MOCKIOBANK_H
#define MOCKIOBANK_H

#include "io/iobank.h"

#include "mem/common/bufferlocation.h"
#include "mem/common/mem_tools.h"

class MockIoBank : public IoBank {
public:
  explicit MockIoBank()
      : IoBank()
      , buffer_(Io.size())
      , loc_(buffer_[0U])
  {
  }

  ILocation8& getLocation8(const address_type address) override
  {
    loc_.setBuffer(buffer_[mem_tools::translateAddressSafe(address, area_)]);
    return loc_;
  }

  static IoBankUP make() { return std::make_unique<MockIoBank>(); }

private:
  std::vector<uint8_t> buffer_;
  BufferLocation loc_;
};

#endif // MOCKIOBANK_H
