#include "gtest/gtest.h"

#include "location/variablelocation.h"

TEST(VariableLocationTest, SingleByte)
{
  auto l = variableLocation(uint8_t { 0xAF });

  EXPECT_FALSE(l->isWord());
  EXPECT_ANY_THROW(l->getWord());
  EXPECT_ANY_THROW(*l = uint16_t { 0xAFFEU });

  EXPECT_EQ(0xAFU, l->getByte());

  *l = uint8_t { 0x42U };

  EXPECT_FALSE(l->isWord());
  EXPECT_ANY_THROW(l->getWord());
  EXPECT_EQ(0x42U, l->getByte());
}

TEST(VariableLocationTest, DoubleByte)
{
  auto l = variableLocation(uint8_t { 0xFEU }, uint8_t { 0xAFU });

  EXPECT_TRUE(l->isWord());
  EXPECT_NO_THROW(l->getWord());

  EXPECT_EQ(0xFEU, l->getByte());
  EXPECT_EQ(0xAFFEU, l->getWord());

  *l = uint16_t { 0x4342U };

  EXPECT_TRUE(l->isWord());
  EXPECT_NO_THROW(l->getWord());

  EXPECT_EQ(0x42U, l->getByte());
  EXPECT_EQ(0x4342U, l->getWord());
}

TEST(VariableLocationTest, Word)
{
  auto l = variableLocation(uint16_t { 0xAFFEU });

  EXPECT_TRUE(l->isWord());
  EXPECT_NO_THROW(l->getWord());

  EXPECT_EQ(0xFEU, l->getByte());
  EXPECT_EQ(0xAFFEU, l->getWord());

  *l = uint16_t { 0x4342U };

  EXPECT_TRUE(l->isWord());
  EXPECT_NO_THROW(l->getWord());

  EXPECT_EQ(0x42U, l->getByte());
  EXPECT_EQ(0x4342U, l->getWord());
}
