#include "gtest/gtest.h"

#include "apu/channel_util/envelope.h"

#include "mock/mockregisteradapter.h"

class EnvelopeTests : public ::testing::Test {
public:
  EnvelopeTests()
      : nrX2(MockRegisterAdapter::make())
  {
  }

protected:
  IRegisterAdapterSP nrX2;
};

TEST(EnvelopeTestsNF, Construction)
{
  EXPECT_ANY_THROW(Envelope c(nullptr));
  EXPECT_NO_THROW(Envelope c(MockRegisterAdapter::make()));
}

TEST_F(EnvelopeTests, Down)
{
  nrX2->set(0b01000010U);

  Envelope e { nrX2 };

  EXPECT_EQ(4U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(4U, e.vol());
  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(3U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(3U, e.vol());
  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(2U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_NO_THROW(e.clock());

  EXPECT_NO_THROW(e.clock());
  EXPECT_NO_THROW(e.clock());

  EXPECT_EQ(0U, e.vol());
  EXPECT_NO_THROW(e.clock());
  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(0U, e.vol());
  EXPECT_NO_THROW(e.clock());
  EXPECT_NO_THROW(e.clock());
}

TEST_F(EnvelopeTests, Up)
{
  nrX2->set(0b11001001U);

  Envelope e { nrX2 };

  EXPECT_EQ(12U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(13U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(14U, e.vol());

  EXPECT_NO_THROW(e.clock());
  EXPECT_NO_THROW(e.clock());

  EXPECT_EQ(15U, e.vol());
  EXPECT_NO_THROW(e.clock());
  EXPECT_EQ(15U, e.vol());
  EXPECT_NO_THROW(e.clock());
}
