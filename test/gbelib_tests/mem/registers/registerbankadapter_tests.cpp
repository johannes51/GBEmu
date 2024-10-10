#include "gtest/gtest.h"

#include "mock/testbank.h"
#include <memory>

#include "location/location.h"

#include "mem/registers/registerbankadapter.h"

class RegisterBankAdapterTest : public ::testing::Test {
public:
  RegisterBankAdapterTest()
      : b(std::make_shared<TestBank>(MemoryArea { 0x0U, 0x1U })) /*, a(b, 0x0U)*/
  {
  }

protected:
  std::shared_ptr<TestBank> b;
  // RegisterBankAdapter a; TODO: nicht abstrakt machen
};

TEST(RegisterBankAdapterTestNF, Construction)
{
  // EXPECT_NO_THROW(( RegisterBankAdapter{ nullptr, 0x00U } )); nicht abstrakt machen
}

TEST_F(RegisterBankAdapterTest, Construction)
{
  *b->getLocation(0x0U) = uint8_t { 0b01010101U };

  //   EXPECT_EQ(0b01010101U, a.get()); nicht abstrakt machen
  //   EXPECT_EQ(1U, a.testBit(0U));
  //   EXPECT_EQ(0U, a.testBit(1U));
  //   EXPECT_EQ(1U, a.testBit(2U));
  //   EXPECT_EQ(0U, a.testBit(3U));
  //   EXPECT_EQ(1U, a.testBit(4U));
  //   EXPECT_EQ(0U, a.testBit(5U));
  //   EXPECT_EQ(1U, a.testBit(6U));
  //   EXPECT_EQ(0U, a.testBit(7U));
}
