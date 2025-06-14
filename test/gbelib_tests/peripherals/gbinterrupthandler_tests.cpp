#include "gtest/gtest.h"

#include "peripherals/gbinterrupthandler.h"

#include "mock/mockiobank.h"
#include "mock/mockregisters.h"
#include "mock/testbank.h"

#include "util/helpers.h"

class GbInterruptHandlerTest : public ::testing::Test {
public:
  GbInterruptHandlerTest()
      : rIe()
  {
  }

protected:
  IoRegister rIe;
  MockIoBank b;
};

TEST_F(GbInterruptHandlerTest, Construction) { EXPECT_NO_THROW((GbInterruptHandler { b, rIe })); }

TEST_F(GbInterruptHandlerTest, IsInterrupt)
{
  auto h = GbInterruptHandler { b, rIe };
  auto* rIf = h.getIf();

  rIf->setByte(0b00000000);
  rIe.setByte(0b00000000);
  EXPECT_FALSE(h.isInterrupt());

  rIf->setByte(0b11100000);
  rIe.setByte(0b01000000);
  EXPECT_FALSE(h.isInterrupt());

  rIf->setByte(0b00001001);
  rIe.setByte(0b00000110);
  EXPECT_FALSE(h.isInterrupt());

  rIf->setByte(0b00001011);
  rIe.setByte(0b00000110);
  EXPECT_TRUE(h.isInterrupt());

  rIf->setByte(0b00000001);
  rIe.setByte(0b00000001);
  EXPECT_TRUE(h.isInterrupt());

  rIf->setByte(0b00011111);
  rIe.setByte(0b00011111);
  EXPECT_TRUE(h.isInterrupt());

  rIf->setByte(0b11100001);
  rIe.setByte(0b11100001);
  EXPECT_TRUE(h.isInterrupt());
}

TEST_F(GbInterruptHandlerTest, Jumps)
{
  auto m = TestBank { { 0x0000U, 0xFFFFU } };
  auto r = MockRegisters {};
  auto h = GbInterruptHandler { b, rIe };
  auto* rIf = h.getIf();

  r.get(WordRegister::PC) = std::uint16_t { 0x1234U };
  rIe.setByte(0xFFU);
  rIf->setByte(0b00000001U); // VBlank

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x1234U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0040U, r.get(WordRegister::PC).get());

  r.get(WordRegister::PC) = std::uint16_t { 0x2345U };
  rIe.setByte(0xFFU);
  rIf->setByte(0b00000010U); // LCD

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x2345U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0048U, r.get(WordRegister::PC).get());

  r.get(WordRegister::PC) = std::uint16_t { 0x3456U };
  rIe.setByte(0xFFU);
  rIf->setByte(0b00000100U); // Timer

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x3456U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0050U, r.get(WordRegister::PC).get());

  r.get(WordRegister::PC) = std::uint16_t { 0x4567U };
  rIe.setByte(0xFFU);
  rIf->setByte(0b00001000U); // Serial

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x4567U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0058U, r.get(WordRegister::PC).get());

  r.get(WordRegister::PC) = std::uint16_t { 0x5678U };
  rIe.setByte(0xFFU);
  rIf->setByte(0b00010000U); // Joypad

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x5678U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0060U, r.get(WordRegister::PC).get());
}

TEST_F(GbInterruptHandlerTest, Priority)
{
  auto m = TestBank { { 0x0000U, 0xFFFFU } };
  auto r = MockRegisters {};
  auto h = GbInterruptHandler { b, rIe };
  auto* rIf = h.getIf();

  r.get(WordRegister::PC) = std::uint16_t { 0x1234U };
  rIe.setByte(0b00001011U);
  rIf->setByte(0b00001001U);

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x1234U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0040U, r.get(WordRegister::PC).get());

  r.get(WordRegister::PC) = std::uint16_t { 0x2345U };

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x2345U, m.getLocation16(hlp::indirect(r.get(WordRegister::SP))).get());
  EXPECT_EQ(0x0058U, r.get(WordRegister::PC).get());
}
