#include "gtest/gtest.h"

#include "peripherals/gbinterrupthandler.h"

#include "mock/mockregisteradapter.h"
#include "mock/mockregisters.h"
#include "mock/testbank.h"

#include "util/helpers.h"

class GbInterruptHandlerTest : public ::testing::Test {
public:
  GbInterruptHandlerTest()
      : rIe(MockRegisterAdapter::make())
      , rIf(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterSP rIe;
  IRegisterAdapterSP rIf;
};

TEST_F(GbInterruptHandlerTest, Construction) { EXPECT_NO_THROW((GbInterruptHandler { rIf, rIe })); }

TEST_F(GbInterruptHandlerTest, IsInterrupt)
{
  auto h = GbInterruptHandler { rIf, rIe };

  rIf->set(0b00000000);
  rIe->set(0b00000000);
  EXPECT_FALSE(h.isInterrupt());

  rIf->set(0b11100000);
  rIe->set(0b01000000);
  EXPECT_FALSE(h.isInterrupt());

  rIf->set(0b00001001);
  rIe->set(0b00000110);
  EXPECT_FALSE(h.isInterrupt());

  rIf->set(0b00001011);
  rIe->set(0b00000110);
  EXPECT_TRUE(h.isInterrupt());

  rIf->set(0b00000001);
  rIe->set(0b00000001);
  EXPECT_TRUE(h.isInterrupt());

  rIf->set(0b00011111);
  rIe->set(0b00011111);
  EXPECT_TRUE(h.isInterrupt());

  rIf->set(0b11100001);
  rIe->set(0b11100001);
  EXPECT_TRUE(h.isInterrupt());
}

TEST_F(GbInterruptHandlerTest, Jumps)
{
  auto m = TestBank { { 0x0000U, 0xFFFFU } };
  auto r = MockRegisters {};
  auto h = GbInterruptHandler { rIf, rIe };

  *r.get(WordRegister::PC) = std::uint16_t { 0x1234U };
  rIe->set(0xFFU);
  rIf->set(0b00000001U); // VBlank

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x1234U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0040U, r.get(WordRegister::PC)->getWord());

  *r.get(WordRegister::PC) = std::uint16_t { 0x2345U };
  rIe->set(0xFFU);
  rIf->set(0b00000010U); // LCD

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x2345U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0048U, r.get(WordRegister::PC)->getWord());

  *r.get(WordRegister::PC) = std::uint16_t { 0x3456U };
  rIe->set(0xFFU);
  rIf->set(0b00000100U); // Timer

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x3456U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0050U, r.get(WordRegister::PC)->getWord());

  *r.get(WordRegister::PC) = std::uint16_t { 0x4567U };
  rIe->set(0xFFU);
  rIf->set(0b00001000U); // Serial

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x4567U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0058U, r.get(WordRegister::PC)->getWord());

  *r.get(WordRegister::PC) = std::uint16_t { 0x5678U };
  rIe->set(0xFFU);
  rIf->set(0b00010000U); // Joypad

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x5678U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0060U, r.get(WordRegister::PC)->getWord());
}

TEST_F(GbInterruptHandlerTest, Priority)
{
  auto m = TestBank { { 0x0000U, 0xFFFFU } };
  auto r = MockRegisters {};
  auto h = GbInterruptHandler { rIf, rIe };

  *r.get(WordRegister::PC) = std::uint16_t { 0x1234U };
  rIe->set(0b00001011U);
  rIf->set(0b00001001U);

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x1234U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0040U, r.get(WordRegister::PC)->getWord());

  *r.get(WordRegister::PC) = std::uint16_t { 0x2345U };

  ASSERT_TRUE(h.isInterrupt());
  h.execute(r, m);
  EXPECT_EQ(0x2345U, m.getLocation(hlp::indirect(*r.get(WordRegister::SP)), true)->getWord());
  EXPECT_EQ(0x0058U, r.get(WordRegister::PC)->getWord());
}
