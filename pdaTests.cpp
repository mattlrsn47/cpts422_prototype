#include <gtest/gtest.h>
#include "pdaHeader.h"

PdaObject pdaObject;

/* FUNCTIONS TO TEST */
void pdaInsert(std::ostream &output, std::istream &input);
void pdaClose();
void pdaDisplay();
//void pdaExit(std::ostream &output); exit() stops test, leave out for now
void pdaHelp();
void pdaList();
void pdaOpen();
void pdaQuit();
void pdaRun();
void pdaSet();
void pdaShow();
void pdaView();

// Sets up generic PDA
void setupPDA()
{
  pdaObject = PdaObject();
  pdaObject.open = true;
  pdaObject.name = "Test";
  pdaObject.description = { "This", "is", "a", "test", "PDA." };
  pdaObject.stateList = { "s0", "s1", "s2" };
  pdaObject.inputAlphabetList = { 'a', 'b' };
  pdaObject.stackAlphabetList = { 'X', 'Y', 'Z' };
  pdaObject.transitionList = {  Transition("s0",'a','X',"s0","XX"),
                                Transition("s0",'a','X',"s1","X"),
                                Transition("s0",'a','Y',"s0","XY"),
                                Transition("s0",'a','Y',"s1","Y"),
                                Transition("s0",'a','Z',"s0","XZ"),
                                Transition("s0",'a','Z',"s1","Z"),
                                Transition("s0",'b','X',"s0","YX"),
                                Transition("s0",'b','X',"s1","X"),
                                Transition("s0",'b','Y',"s0","YY"),
                                Transition("s0",'b','Y',"s1","Y"),
                                Transition("s0",'b','Z',"s0","YZ"),
                                Transition("s0",'b','Z',"s1","Z"),
                                Transition("s1",'a','X',"s1","\\"),
                                Transition("s1",'b','Y',"s1","\\"),
                                Transition("s1",'\\','Z',"s2","\\")
                              };
  pdaObject.initialState = "s0";
  pdaObject.startCharacter = 'Z';
  pdaObject.finalStateList = { "s2" };
  pdaObject.inputStringList = { "aba", "ab", "\\" };
  pdaObject.stringListChanged = false;
  pdaObject.maximumTransitions = 1;
  pdaObject.maximumCharacters = 32;
  pdaObject.status = NOT_YET_RUN;
  pdaObject.accepted = false;
  pdaObject.rejected = false;
  pdaObject.originalInputString = "";
  pdaObject.branchList = {};
  pdaObject.totalTransitions = 0;
}

/* Insert1: string successfully add to list */
TEST(Insert, insert1)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  std::string newInputString = "abba";
  std::string expectedOutput = "String to insert into list: "+newInputString+" successfully added to list!\n\n";
  input.str(newInputString);
  std::list<std::string> expectedStringList = pdaObject.inputStringList;
  expectedStringList.push_back(newInputString);

  // test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);
  EXPECT_EQ(pdaObject.inputStringList, expectedStringList);
  EXPECT_EQ(pdaObject.stringListChanged, true);
  
  // revert any changesto PDA
  setupPDA();
}

/* Insert2: pda is not open */
TEST(Insert, insert2)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  pdaObject.open = false;
  std::string expectedOutput = "No PDA is open to add input strings for!\n\n";

  //test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);

  // revert any changes to PDA
  setupPDA();
}

/* Insert3: string has space in it */

/* Insert4: string contatins chars not in input alphabet */

/* Insert5: string already in list */
TEST(Insert, insert5)
{
  // input and output streams
  std::stringstream input;
  std::stringstream output;

  // test setup
  std::string expectedOutput = "String to insert into list: String is already in list!\n\n";
  input.str("aba");

  //test
  pdaInsert(output, input);
  EXPECT_EQ(output.str(), expectedOutput);
  EXPECT_EQ(pdaObject.stringListChanged, false);

  // revert any changes to PDA
  setupPDA();
}

int main(int argc, char **argv) {
  setupPDA(); // initialize test object
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}