#include "gtest/gtest.h"

#include "cpu/id/opcodeview.h"

TEST(OpcodeViewTest, All)
{
  OpcodeView opc(0xA3);
  EXPECT_EQ(0xA3U, opc.value());
  EXPECT_EQ(0x3U, opc.lowerNibble());
  EXPECT_EQ(0xAU, opc.upperNibble());
}
