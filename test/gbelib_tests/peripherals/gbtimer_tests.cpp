#include "gtest/gtest.h"

#include "peripherals/gbtimer.h"

#include "mock/mockiobank.h"
#include "mock/mockregisteradapter.h"

#include "peripherals/gbinterrupthandler.h"

class GbTimerTest : public ::testing::Test {
public:
  GbTimerTest()
      : div_apu_()
      , if_()
  {
  }

protected:
  IoRegister div_apu_;
  IoRegister if_;
  MockIoBank b_;

  void SetUp() override
  {
    div_apu_.setByte(0U);
    if_.setByte(0U);
  }
};

TEST_F(GbTimerTest, Construction) { EXPECT_NO_THROW((GbTimer { b_, div_apu_, if_ })); }

TEST_F(GbTimerTest, Interrupt)
{
  GbTimer t { b_, div_apu_, if_ };
  t.getTac()->setByte(0b101U); // Every 4 clocks
  t.getTma()->setByte(0xFDU); // Every 3 increments
  t.getTima()->setByte(0xFEU); // 2 increments away

  t.clock();
  EXPECT_EQ(0xFEU, t.getTima()->getByte());
  EXPECT_FALSE(if_.testBit(TimerInterruptBit));

  t.clock();
  EXPECT_EQ(0xFEU, t.getTima()->getByte());
  EXPECT_FALSE(if_.testBit(TimerInterruptBit));

  t.clock();
  t.clock();
  EXPECT_EQ(0xFFU, t.getTima()->getByte());
  EXPECT_FALSE(if_.testBit(TimerInterruptBit));

  t.clock();
  t.clock();
  t.clock();
  EXPECT_NE(0xFDU, t.getTima()->getByte());
  EXPECT_FALSE(if_.testBit(TimerInterruptBit));
  t.clock();
  EXPECT_EQ(0xFDU, t.getTima()->getByte());
  EXPECT_TRUE(if_.testBit(TimerInterruptBit));
}

TEST_F(GbTimerTest, SysTimerBit)
{
  GbTimer t { b_, div_apu_, if_ };

  t.getTac()->setByte(0b100U); // Every 256 clocks
  t.clock();
  EXPECT_EQ(0U, t.getTima()->getByte());

  t.getTac()->setByte(0b101U); // Every 4 clocks
  t.clock();
  EXPECT_EQ(0U, t.getTima()->getByte());

  t.getTac()->setByte(0b110U); // Every 16 clocks
  t.clock();
  EXPECT_EQ(1U, t.getTima()->getByte());

  t.getTac()->setByte(0b111U); // Every 64 clocks
  t.clock();
  EXPECT_EQ(1U, t.getTima()->getByte());
}

TEST_F(GbTimerTest, DivApu)
{
  GbTimer t { b_, div_apu_, if_ };

  t.clock();
  EXPECT_EQ(0x0U, div_apu_.getByte());

  t.clock();
  EXPECT_EQ(0x0U, div_apu_.getByte());

  for (auto i = 0U; i < 2046U; ++i) {
    t.clock();
  }

  EXPECT_EQ(0x1U, div_apu_.getByte());
}
