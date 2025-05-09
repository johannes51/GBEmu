#include "gtest/gtest.h"

#include "location/variablelocation.h"

TEST(VariableLocationTest, SingleByte)
{
  Location8UP l = variableLocation(uint8_t { 0xAF });

  EXPECT_NO_THROW(l->get());
  EXPECT_EQ(0xAFU, l->get());

  *l = uint8_t { 0x42U };

  EXPECT_EQ(0x42U, l->get());
}

TEST(VariableLocationTest, DoubleByte)
{
  Location16UP l = variableLocation(uint8_t { 0xFEU }, uint8_t { 0xAFU });

  EXPECT_NO_THROW(l->get());
  EXPECT_EQ(0xAFFEU, l->get());

  *l = uint16_t { 0x4342U };

  EXPECT_EQ(0x4342U, l->get());
}

TEST(VariableLocationTest, Word)
{
  Location16UP l = variableLocation(uint16_t { 0xAFFEU });

  EXPECT_NO_THROW(l->get());
  EXPECT_EQ(0xAFFEU, l->get());

  *l = uint16_t { 0x4342U };

  EXPECT_EQ(0x4342U, l->get());
}
