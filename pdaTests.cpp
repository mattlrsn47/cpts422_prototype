#include <gtest/gtest.h>
#include "pdaHeader.h"

PdaObject pdaObject;
//void pdaClose();
void pdaExit(std::ostream &output);


TEST(SuiteOne, testOne)
{
  pdaObject = PdaObject();
  // here: set any values needed in pda for the function to work
  pdaObject.name = "Test"; // <-- example
  std::string expectedOutput = "Successfully exited application\n\n";
  std::stringstream actualOutput;
  pdaExit(actualOutput);
  EXPECT_EQ(actualOutput.str(), expectedOutput);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}