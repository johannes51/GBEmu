#include "gtest/gtest.h"

#include "apu/channel_util/length.h"

#include "mock/mockregisteradapter.h"

class LengthTests : public ::testing::Test {
public:
  LengthTests()
      : nrX1(MockRegisterAdapter::make())
      , nrX4(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterUP nrX1;
  IRegisterAdapterUP nrX4;
};

TEST(LengthTestsNF, Construction)
{
  EXPECT_NO_THROW(Length l(*MockRegisterAdapter::make(), *MockRegisterAdapter::make()));
}

TEST_F(LengthTests, Standard)
{
  nrX1->setByte(0x1FU);
  nrX4->setByte(0b01000000U);

  Length l { *nrX1, *nrX4 };

  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  for (auto i = 0x20U; i < 0x3FU; ++i) {
    EXPECT_NO_THROW(l.clock()) << std::hex << i;
    EXPECT_FALSE(l.isRunOut()) << std::hex << i;
  }
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());
}

TEST_F(LengthTests, Restart)
{
  nrX1->setByte(0x3FU);
  nrX4->setByte(0b01000000U);

  Length l { *nrX1, *nrX4 };

  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());

  nrX4->setByte(0b00000000U);
  nrX1->setByte(0x3DU);

  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nrX4->setByte(0b01000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nrX4->setByte(0b00000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nrX4->setByte(0b01000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());
}
