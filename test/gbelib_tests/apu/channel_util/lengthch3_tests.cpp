#include "gtest/gtest.h"

#include "apu/channel_util/lengthch3.h"

#include "mock/mockregisteradapter.h"

class LengthCh3Tests : public ::testing::Test {
public:
  LengthCh3Tests()
      : nr31(MockRegisterAdapter::make())
      , nr34(MockRegisterAdapter::make())
  {
  }

protected:
  std::shared_ptr<IRegisterAdapter> nr31;
  std::shared_ptr<IRegisterAdapter> nr34;
};

TEST(LengthCh3TestsNF, Construction)
{
  EXPECT_NO_THROW(LengthCh3 l(*MockRegisterAdapter::make(), *MockRegisterAdapter::make()));
}

TEST_F(LengthCh3Tests, Standard)
{
  nr31->setByte(0xEFU);
  nr34->setByte(0b01000000U);

  LengthCh3 l { *nr31, *nr34 };

  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  for (auto i = 0xF0U; i < 0xFEU; ++i) {
    EXPECT_NO_THROW(l.clock()) << std::hex << i;
    EXPECT_FALSE(l.isRunOut()) << std::hex << i;
  }
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());
}

TEST_F(LengthCh3Tests, Restart)
{
  nr31->setByte(0xFEU);
  nr34->setByte(0b01000000U);

  LengthCh3 l { *nr31, *nr34 };

  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());

  nr34->setByte(0b00000000U);
  nr31->setByte(0xFCU);

  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nr34->setByte(0b01000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nr34->setByte(0b00000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());

  nr34->setByte(0b01000000U);
  EXPECT_NO_THROW(l.clock());
  EXPECT_NO_THROW(l.clock());
  EXPECT_FALSE(l.isRunOut());
  EXPECT_NO_THROW(l.clock());
  EXPECT_TRUE(l.isRunOut());
}
