#ifndef TESTBANK_H
#define TESTBANK_H

#include "mem/imemorywordview.h"

#include "mem/common/bytewriterlocation16.h"
#include "mem/ram/rambank.h"

#include <vector>

class TestBank : public IMemoryWordView {
public:
  TestBank(const MemoryArea& area);

  static IMemoryWordView& staticBank();

  ILocation8& getLocation8(const address_type address) override;
  ILocation16& getLocation16(const address_type address) override;

private:
  static std::vector<uint8_t> buffer_;
  RamBank b_;
  ByteWriterLocation16 l;
};

#endif // TESTBANK_H
