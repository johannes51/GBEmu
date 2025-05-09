#include "gtest/gtest.h"

#include "peripherals/gbtimer.h"

#include "mock/mockdivregister.h"
#include "mock/mockregisteradapter.h"

#include "peripherals/gbinterrupthandler.h"

using ::testing::Return;
using ::testing::StrictMock;

class GbTimerTest : public ::testing::Test {
public:
  GbTimerTest()
      : div_(MockDivRegister::make())
      , div_apu_(MockRegisterAdapter::make())
      , tima_(MockRegisterAdapter::make())
      , tma_(MockRegisterAdapter::make())
      , tac_(MockRegisterAdapter::make())
      , if_(MockRegisterAdapter::make())
  {
  }

protected:
  std::shared_ptr<StrictMock<MockDivRegister>> div_;
  IRegisterAdapterSP div_apu_;
  IRegisterAdapterSP tima_;
  IRegisterAdapterSP tma_;
  IRegisterAdapterSP tac_;
  IRegisterAdapterSP if_;

  void SetUp() override
  {
    EXPECT_CALL(*div_, set(0U)).WillOnce(Return());
    div_->set(0U);
    div_apu_->set(0U);
    tima_->set(0U);
    tma_->set(0U);
    if_->set(0U);
  }
};

TEST_F(GbTimerTest, Construction) { EXPECT_NO_THROW((GbTimer { div_, div_apu_, tima_, tma_, tac_, if_ })); }

TEST_F(GbTimerTest, Interrupt)
{
  GbTimer t { div_, div_apu_, tima_, tma_, tac_, if_ };
  tac_->set(0b101U); // Every 4 clocks
  tma_->set(0xFDU); // Every 3 increments
  tima_->set(0xFEU); // 2 increments away

  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0xFEU, tima_->get());
  EXPECT_FALSE(if_->testBit(TimerInterruptBit));

  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(true));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0xFEU, tima_->get());
  EXPECT_FALSE(if_->testBit(TimerInterruptBit));

  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0xFFU, tima_->get());
  EXPECT_FALSE(if_->testBit(TimerInterruptBit));

  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(true));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0xFDU, tima_->get());
  EXPECT_TRUE(if_->testBit(TimerInterruptBit));
}

TEST_F(GbTimerTest, SysTimerBit)
{
  GbTimer t { div_, div_apu_, tima_, tma_, tac_, if_ };

  tac_->set(0b100U); // Every 256 clocks
  EXPECT_CALL(*div_, testBitSystemTimer(7U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0U, tima_->get());

  tac_->set(0b101U); // Every 4 clocks
  EXPECT_CALL(*div_, testBitSystemTimer(1U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0U, tima_->get());

  tac_->set(0b110U); // Every 16 clocks
  EXPECT_CALL(*div_, testBitSystemTimer(3U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0U, tima_->get());

  tac_->set(0b111U); // Every 64 clocks
  EXPECT_CALL(*div_, testBitSystemTimer(5U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0U, tima_->get());
}

TEST_F(GbTimerTest, DivApu)
{
  GbTimer t { div_, div_apu_, tima_, tma_, tac_, if_ };

  EXPECT_CALL(*div_, testBitSystemTimer(7U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0x0U, div_apu_->get());

  EXPECT_CALL(*div_, testBitSystemTimer(7U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(true));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0x0U, div_apu_->get());

  EXPECT_CALL(*div_, testBitSystemTimer(7U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, testBitSystemTimer(10U)).WillOnce(Return(false));
  EXPECT_CALL(*div_, clock()).WillOnce(Return());
  t.clock();
  EXPECT_EQ(0x1U, div_apu_->get());
}
