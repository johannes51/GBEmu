#include "gtest/gtest.h"

#include "mem/mem_tools.h"

TEST(MemoryToolsTest, TranslateAddressSafe)
{
  address_type inputAddress = 0x00;
  MemoryArea area { 1, 16 };

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, area));
}

TEST(MemoryToolsTest, TranslateAddressSafe2)
{
  address_type inputAddress = 0x01;
  MemoryArea area { 1, 16 };

  address_type result = 0;
  ASSERT_NO_THROW(result = mem_tools::translateAddressSafe(inputAddress, area));

  EXPECT_EQ(inputAddress - area.from, result);
}

TEST(MemoryToolsTest, TranslateAddressSafe3)
{
  address_type inputAddress = 0x10;
  MemoryArea area { 0x00, 0x0F };

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, area));
}

TEST(MemoryToolsTest, TranslateAddressSafe4)
{
  address_type inputAddress = 0x00;
  address_type startAddress = 1;
  address_type size = 16;

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, startAddress, size));
}

TEST(MemoryToolsTest, TranslateAddressSafe5)
{
  address_type inputAddress = 0x05;
  address_type startAddress = 1;
  address_type size = 16;

  address_type result = 0;
  ASSERT_NO_THROW(result = mem_tools::translateAddressSafe(inputAddress, startAddress, size));

  EXPECT_EQ(inputAddress - startAddress, result);
}

TEST(MemoryToolsTest, TranslateAddressSafe6)
{
  address_type inputAddress = 0x10;
  address_type startAddress = 0;
  address_type size = 16;

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, startAddress, size));
}

TEST(MemoryToolsTest, TranslateAddressSafe7)
{
  address_type inputAddress = 0x00;
  MemoryArea area { 1, 16 };
  address_type offset = 20;

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, area, offset));
}

TEST(MemoryToolsTest, TranslateAddressSafe8)
{
  address_type inputAddress = 0x04;
  MemoryArea area { 1, 16 };
  address_type offset = 20;

  address_type result = 0;
  ASSERT_NO_THROW(result = mem_tools::translateAddressSafe(inputAddress, area, offset));

  EXPECT_EQ(inputAddress + offset, result);
}

TEST(MemoryToolsTest, TranslateAddressSafe9)
{
  address_type inputAddress = 0x17;
  MemoryArea area { 1, 16 };
  address_type offset = 20;

  EXPECT_ANY_THROW(mem_tools::translateAddressSafe(inputAddress, area, offset));
}

TEST(MemoryToolsTest, IsDisjunct)
{
  std::vector<MemoryArea> areas(2);
  areas.at(0) = { 0, 15 };
  areas.at(1) = { 32, 63 };
  MemoryArea area { 15, 31 };

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, IsDisjunct2)
{
  std::vector<MemoryArea> areas(2);
  areas.at(0) = { 0, 15 };
  areas.at(1) = { 32, 63 };
  MemoryArea area { 16, 31 };

  EXPECT_TRUE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, IsDisjunct3)
{
  std::vector<MemoryArea> areas(2);
  areas.at(0) = { 0, 15 };
  areas.at(1) = { 32, 63 };
  MemoryArea area { 16, 32 };

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, IsDisjunct4)
{
  std::vector<MemoryArea> areas(2);
  areas.at(0) = { 0, 15 };
  areas.at(1) = { 32, 63 };
  MemoryArea area { 15, 32 };

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}
