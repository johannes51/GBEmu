#include "gtest/gtest.h"

#include "util/fallingedgedetector.h"

TEST(FallingEdgeDetectorTest, Construction)
{
  EXPECT_NO_THROW(FallingEdgeDetector<int> f);
  EXPECT_NO_THROW(FallingEdgeDetector<unsigned> f);
  EXPECT_NO_THROW(FallingEdgeDetector<int> f(1));
  EXPECT_NO_THROW((FallingEdgeDetector<unsigned, 1>(2)));
}

TEST(FallingEdgeDetectorTest, AbInitio)
{
  FallingEdgeDetector<int, -1> f(-1);

  EXPECT_FALSE(f.isFallingEdge(-1));
  EXPECT_FALSE(f.isFallingEdge(1));
  EXPECT_TRUE(f.isFallingEdge(-1));
}

TEST(FallingEdgeDetectorTest, Standard)
{
  FallingEdgeDetector<uint8_t> f(0);

  EXPECT_FALSE(f.isFallingEdge(0));
  EXPECT_FALSE(f.isFallingEdge(1));
  EXPECT_TRUE(f.isFallingEdge(0));
  EXPECT_FALSE(f.isFallingEdge(0));
  EXPECT_FALSE(f.isFallingEdge(1));
  EXPECT_FALSE(f.isFallingEdge(2));
  EXPECT_FALSE(f.isFallingEdge(3));
  EXPECT_TRUE(f.isFallingEdge(0));
}
