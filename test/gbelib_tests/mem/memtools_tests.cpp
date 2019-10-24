#include "gtest/gtest.h"

#include "mem/mem_tools.h"

TEST(MemoryToolsTest, testTranslateAdressSafe) {
  address_type inputAddress = 0x00;
  MemoryArea area{1,16};

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, area));
}

TEST(MemoryToolsTest, testTranslateAdressSafe2) {
  address_type inputAddress = 0x01;
  MemoryArea area{1,16};

  address_type result;
  ASSERT_NO_THROW(result = mem_tools::translateAdressSafe(inputAddress, area));

  EXPECT_EQ(inputAddress - area.from, result);
}

TEST(MemoryToolsTest, testTranslateAdressSafe3) {
  address_type inputAddress = 0x10;
  MemoryArea area{0x00,0x0F};

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, area));
}

TEST(MemoryToolsTest, testTranslateAdressSafe4) {
  address_type inputAddress = 0x00;
  address_type startAddress = 1;
  address_type size = 16;

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, startAddress, size));
}

TEST(MemoryToolsTest, testTranslateAdressSafe5) {
  address_type inputAddress = 0x05;
  address_type startAddress = 1;
  address_type size = 16;

  address_type result;
  ASSERT_NO_THROW(result = mem_tools::translateAdressSafe(inputAddress, startAddress, size));

  EXPECT_EQ(inputAddress - startAddress, result);
}

TEST(MemoryToolsTest, testTranslateAdressSafe6) {
  address_type inputAddress = 0x10;
  address_type startAddress = 0;
  address_type size = 16;

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, startAddress, size));
}

TEST(MemoryToolsTest, testTranslateAdressSafe7) {
  address_type inputAddress = 0x00;
  MemoryArea area{1,16};
  address_type offset = 20;

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, area, offset));
}

TEST(MemoryToolsTest, testTranslateAdressSafe8) {
  address_type inputAddress = 0x04;
  MemoryArea area{1,16};
  address_type offset = 20;

  address_type result;
  ASSERT_NO_THROW(result = mem_tools::translateAdressSafe(inputAddress, area, offset));

  EXPECT_EQ(inputAddress + offset, result);
}

TEST(MemoryToolsTest, testTranslateAdressSafe9) {
  address_type inputAddress = 0x17;
  MemoryArea area{1,16};
  address_type offset = 20;

  EXPECT_ANY_THROW(mem_tools::translateAdressSafe(inputAddress, area, offset));
}

TEST(MemoryToolsTest, testIsDisjunct) {
  std::vector<MemoryArea> areas(2);
  areas.at(0) = {0,15};
  areas.at(1) = {32,63};
  MemoryArea area{15,31};

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, testIsDisjunct2) {
  std::vector<MemoryArea> areas(2);
  areas.at(0) = {0,15};
  areas.at(1) = {32,63};
  MemoryArea area{16,31};

  EXPECT_TRUE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, testIsDisjunct3) {
  std::vector<MemoryArea> areas(2);
  areas.at(0) = {0,15};
  areas.at(1) = {32,63};
  MemoryArea area{16,32};

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}

TEST(MemoryToolsTest, testIsDisjunct4) {
  std::vector<MemoryArea> areas(2);
  areas.at(0) = {0,15};
  areas.at(1) = {32,63};
  MemoryArea area{15,32};

  EXPECT_FALSE(mem_tools::isDisjunct(area, areas));
}

