#ifndef TESTBANK_H
#define TESTBANK_H

#include "mem/ram/rambank.h"

class TestBank : public RamBank {
public:
  TestBank(const MemoryArea& area);

private:
  static std::vector<uint8_t> buffer_;
};

#endif // TESTBANK_H
