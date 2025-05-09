#include "gtest/gtest.h"

#include "mock/mockregisteradapter.h"

#include "ppu/ppu.h"

TEST(PpuTest, Construction) { EXPECT_NO_THROW(Ppu p(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr)); }

TEST(PpuTest, Clock)
{
  Ppu p(nullptr, MockRegisterAdapter::make(), MockRegisterAdapter::make(), MockRegisterAdapter::make(),
      MockRegisterAdapter::make(), MockRegisterAdapter::make());
  EXPECT_NO_THROW(p.clock());
}
