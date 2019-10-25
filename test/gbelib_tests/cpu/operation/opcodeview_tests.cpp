#include "gtest/gtest.h"

#include "cpu/operation/opcodeview.h"

TEST(OpcodeViewTest, test) {
  OpcodeView opc(0xA3);
  EXPECT_EQ(0xA3, opc.value());
  EXPECT_EQ(0x3, opc.lowerNibble());
  EXPECT_EQ(0xA, opc.upperNibble());
}
