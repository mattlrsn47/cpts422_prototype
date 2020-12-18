#include <gtest/gtest.h>
#include "pdaHeader.h"

PdaObject pdaObject;

/* FUNCTIONS TO TEST */
void pdaInsert(std::ostream &output, std::istream &input);
void pdaClose(std::ostream &output);
void pdaDisplay(std::ostream &output);
//void pdaExit(std::ostream &output); exit() stops test, leave out for now
void pdaHelp(std::ostream &output);
void pdaList(std::ostream &output);
void pdaOpen(std::ostream &output, std::istream &input);
void pdaQuit(std::ostream &output);
void pdaRun(std::ostream &output, std::istream &input);
void pdaSet(std::ostream &output, std::istream &input);
void pdaShow(std::ostream &output);
void pdaView(std::ostream &output);

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

/* Close1: no changes to input strings */

/* Close2: changes made to input strings */

/* Close3: pda is not open */

/* Display1: pda has not yet run */

/* Display2: multiple branches */

/* Display3: pda is not open */

/* Help */

/* List1: no strings in list */

/* List2: multiple strings in list */

/* List3: pda is not open */

/* Open1: use "test" files */

/* Open2: invalid file */

/* Open3: a pda is already open */

/* Quit1: successfully quit */

/* Quit2: pda not running */

/* Quit3: pda is not open */

/* Run1: pda not already running, select string */

/* Run2: pda is running, continuation */

/* Run3: accepted string */

/* Run4: rejected string */

/* Run5: pda is not open */

/* Set1: successfully set transitions */

/* Set2: attempt value with a space */

/* Set3: attempt value less than 1 */

/* Set4: pda is not open */

/* Show1: pda has not yet run */

/* Show2: pda is running */

/* Show3: pda is not running */

/* Show4: pda is not open */

/* View1: successfully view pda */

/* View2: pda is not open */

int main(int argc, char **argv) {
  setupPDA(); // initialize test object
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}