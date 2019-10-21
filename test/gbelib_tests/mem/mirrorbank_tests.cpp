#include "gtest/gtest.h"

#include "mem/mirrorbank.h"
#include "mem/rambank.h"
#include "location/location.h"


using namespace std;

TEST(MirrorBankTest, testIndirect) {
  auto b = std::make_shared<RamBank>(MemoryArea{0, 15});
  auto writeByte = b->getByte(4);
  uint8_t value = 0xA2;
  writeByte->set(value);

  MirrorBank m{{16, 31}, {0, 15}, b};

  auto readByte = m.getByte(16 + 4);
  ASSERT_EQ(value, readByte->get());
}

