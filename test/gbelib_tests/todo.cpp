#include "gtest/gtest.h"

#include "cpu/id/instructiondecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(TodoTest, testUnimplemented)
{
  EXPECT_ANY_THROW(id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x0F))));
  EXPECT_ANY_THROW(id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0xCB))));
  EXPECT_ANY_THROW(id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0xC1))));
}
