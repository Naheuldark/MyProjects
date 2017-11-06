#include "gtest/gtest.h"
#include "Dvector.h"

class DvectorTest: public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

TEST_F(DvectorTest,constructor){
    Dvector vec(3,1);
    EXPECT_EQ(3,vec.size());
    EXPECT_EQ(1,vec(2));
}
